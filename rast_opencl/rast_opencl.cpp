#pragma once
#define CL_USE_DEPRECATED_OPENCL_1_2_APIS
#include <CL/cl.h>

#include <algorithm>
#include <cstdint>
#include <array>

#include <intrin.h>

#include "../source/context.h"
#include "../source/math.h"
#include "../source/raster.h"
#include "../source/texture.h"

namespace {

struct frame_t {
  uint32_t w, h;
  uint32_t num_w, num_h;
};

const char *cl_kernel_raster = R"(
struct __attribute__ ((packed)) vertex_t {
  float4 coord;
  float4 rgba;
  float2 tex;
};

struct __attribute__ ((packed)) triangle_t {
  struct vertex_t vert[3];
};

float triangle_area(const float2 v0,
                    const float2 v1,
                    const float2 v2) {

  // area is found using part of the vector product

  // x = a2 * b3 - a3 * b2
  // y = a1 * b3 - a3 * b1
  // z = a1 * b2 - a2 * b1

  // where a = v0 -> v1
  // where b = v0 -> v2

  // we only care about the z componant which contains the area of the
  // parallelogram formed. i'm unsure why we dont need to multiply by
  // 0.5f however when returning the result.

  return (v1.x - v0.x) * (v2.y - v0.y) - (v2.x - v0.x) * (v1.y - v0.y);
}

// evaluate the gradient field given the following:
//  normal:   the normal for that edge
//  poe:      a point on the edge
//  point:    the location where to sample it
float evaluate(const float2 normal,
               const float2 poe,
               const float2 point) {
  return dot(normal, point) - dot(normal, poe);
}

float2 cross2d(const float2 a) {
  return (float2)(-a.y, a.x );
}

kernel void raster(__global const struct triangle_t *tri,
                   const uint num_tri,
                   __global uint *fb_color,
                   __global float *fb_depth,
                   uint fb_pitch) {

  // chunk bounding rect
  const float chunk_min_x = get_group_id(0) * CHUNK_SIZE;
  const float chunk_min_y = get_group_id(1) * CHUNK_SIZE;
  const float chunk_max_x =     chunk_min_x + CHUNK_SIZE;
  const float chunk_max_y =     chunk_min_y + CHUNK_SIZE;

  // offset the framebuffer
  const uint fb_offs = get_group_id(0) * CHUNK_SIZE +
                       get_group_id(1) * CHUNK_SIZE * fb_pitch;
  fb_color += fb_offs;
  fb_depth += fb_offs;

  // chunk staring coordinate
  const float2 start = (float2)(chunk_min_x, chunk_min_y);

  // for each triangle
  for (uint t=0; t < num_tri; ++t) {

    // get the vertices
    const float2 v0 = tri[t].vert[0].coord.xy;
    const float2 v1 = tri[t].vert[2].coord.xy;
    const float2 v2 = tri[t].vert[1].coord.xy;

    // find the area of the triangle
    const float area = triangle_area(v0, v1, v2);

    // find edge vectors
    const float2 d12 = v2 - v1;
    const float2 d20 = v0 - v2;

    // cross product gives us normals from the edges
    // which we 'normalize' to the area of the triangle
    const float2 n0 = cross2d(d12) / area;
    const float2 n1 = cross2d(d20) / area;

    // edge functions are
    //  s0 = dot(n0, point) - d0
    //  s1 = dot(n1, point) - d1
    //  s2 = dot(n2, point) - d2

    // evaluate the starting position for each interpolant
    float s0 = evaluate(n0, v1, start);
    float s1 = evaluate(n1, v2, start);

    for (int y = 0; y < CHUNK_SIZE; y += 1) {

      float s0_ = s0;
      float s1_ = s1;

      for (int x = 0; x < CHUNK_SIZE; x += 1) {

        // s2_ can be derived from s0_ and s1_ since we know the
        // sum of them all should add up to 1.0f (the full area)
        const float s2_ = 1.f - (s0_ + s1_);

        if (s0_ > 0 && s1_ > 0 && s2_ > 0) {
          const uchar r = (uchar)(s0_ * 256);
          const uchar g = (uchar)(s1_ * 256);
          const uchar b = (uchar)(s2_ * 256);
          const uint rgb = (r << 16) | (g << 8) | b;

          fb_color[ x + y * fb_pitch ] = rgb;
        }

        s0_ += n0.x;
        s1_ += n1.x;
      }

      s0 += n0.y;
      s1 += n1.y;
    }

  }
}
)";

} // namespace

struct rast_opencl_t : public raster_t {

  static const uint32_t chunk_size = 32;

  rast_opencl_t()
    : _cl_context(nullptr)
    , _cl_device(nullptr)
    , _cl_queue(nullptr)
    , _cl_program(nullptr)
    , _cl_kernel(nullptr)
    , _cl_fb_color(nullptr)
    , _cl_fb_depth(nullptr)
    , _cl_triangles(nullptr)
    , _cl_triangle_setup(nullptr)
    , _cxt(nullptr) {
  }

  void framebuffer_release() override {
    if (_cl_fb_color) {
      clReleaseMemObject(_cl_fb_color);
      _cl_fb_color = nullptr;
    }
    if (_cl_fb_depth) {
      clReleaseMemObject(_cl_fb_depth);
      _cl_fb_depth = nullptr;
    }
  }

  void framebuffer_aquire() override {

    if (!_cl_context || !_cxt) {
      return;
    }

    // release the old framebuffer
    framebuffer_release();

    // start with framebuffer size
    uint32_t w = _cxt->buffer.width();
    uint32_t h = _cxt->buffer.height();

    // round to nearest chunk size
    const uint32_t chunk_mask = chunk_size - 1;
    w = (w + chunk_mask) & ~chunk_mask;
    h = (h + chunk_mask) & ~chunk_mask;

    _frame.w = w;
    _frame.h = h;
    _frame.num_w = w / chunk_size;
    _frame.num_h = h / chunk_size;

    const size_t fb_area = w * h;

    // create the color buffer
    _cl_fb_color = clCreateBuffer(
      _cl_context,
      CL_MEM_READ_WRITE,
      fb_area * sizeof(uint32_t),
      nullptr,
      nullptr);
    // create the depth buffer
    _cl_fb_depth = clCreateBuffer(
      _cl_context,
      CL_MEM_READ_WRITE,
      fb_area * sizeof(float),
      nullptr,
      nullptr);

  }

  bool start(gl_context_t &cxt) override {
    _cxt = &cxt;

    // access an OpenCL device
    if (!init_cl()) {
      return false;
    }

    // triangle list buffer
    _cl_triangles = clCreateBuffer(
      _cl_context,
      CL_MEM_READ_WRITE,
      1024 * 1024 * 16,  // 16meg
      nullptr,
      nullptr);
    if (!_cl_triangles) {
      return false;
    }

    // triangle setup buffer
    _cl_triangle_setup = clCreateBuffer(
      _cl_context,
      CL_MEM_READ_WRITE,
      1024 * 1024 * 16,  // 16meg
      nullptr,
      nullptr);
    if (!_cl_triangle_setup) {
      return false;
    }

    if (!compile_kernel()) {
      return false;
    }

    return true;
  }

  void stop() override {
    if (_cl_triangles) {
      clReleaseMemObject(_cl_triangles);
      _cl_triangles = nullptr;
    }
    if (_cl_triangle_setup) {
      clReleaseMemObject(_cl_triangle_setup);
      _cl_triangle_setup = nullptr;
    }
    if (_cl_fb_color) {
      clReleaseMemObject(_cl_fb_color);
      _cl_fb_color = nullptr;
    }
    if (_cl_fb_depth) {
      clReleaseMemObject(_cl_fb_depth);
      _cl_fb_depth = nullptr;
    }
    if (_cl_kernel) {
      clReleaseKernel(_cl_kernel);
      _cl_kernel = nullptr;
    }
    if (_cl_program) {
      clReleaseProgram(_cl_program);
      _cl_program = nullptr;
    }
    if (_cl_queue) {
      clReleaseCommandQueue(_cl_queue);
      _cl_queue = nullptr;
    }
    if (_cl_context) {
      clReleaseContext(_cl_context);
      _cl_context = nullptr;
    }
    _cxt = nullptr;
  }

  void push_triangles(const std::vector<triangle_t> &triangles,
                      const texture_t *tex,
                      const state_manager_t &state) override {

    if (!_cl_triangles || !_cl_queue) {
      return;
    }

    cl_int ret = CL_SUCCESS;

    // write triangles into the triangle list buffer
    ret = clEnqueueWriteBuffer(
      _cl_queue,
      _cl_triangles,
      false,
      0,
      triangles.size() * sizeof(triangle_t),
      triangles.data(),
      0,
      0,
      nullptr
    );
    if (ret != CL_SUCCESS) {
      DEBUG_BREAK;
      return;
    }

    // triangle setup kernel
    // ...

    // set kernel parameters
    {
      const cl_uint num_triangles = triangles.size();
      const cl_uint fp_pitch = _frame.w;
      clSetKernelArg(_cl_kernel, 0, sizeof(_cl_triangles), &_cl_triangles);
      clSetKernelArg(_cl_kernel, 1, sizeof(cl_uint),       &num_triangles);
      clSetKernelArg(_cl_kernel, 2, sizeof(_cl_fb_color),  &_cl_fb_color);
      clSetKernelArg(_cl_kernel, 3, sizeof(_cl_fb_depth),  &_cl_fb_depth);
      clSetKernelArg(_cl_kernel, 4, sizeof(cl_uint),       &fp_pitch);
    }

    // triangle raster kernel
    size_t gwgs[3] = { _frame.num_w, _frame.num_h, 1 };
    size_t lwgs[3] = { 1, 1, 1 };
    ret = clEnqueueNDRangeKernel(
      _cl_queue,
      _cl_kernel,
      2,
      nullptr,
      gwgs,
      lwgs,
      0,
      0,
      nullptr);
    if (ret != CL_SUCCESS) {
      DEBUG_BREAK;
      return;
    }

    clFinish(_cl_queue);
  }

  void flush() override {}

  void present() override {

    if (!_cl_fb_color || !_cl_queue || !_cxt) {
      return;
    }

    // TODO: use clEnqueueReadBufferRect since our rendertarget
    //       and the actual screen buffer might be different sizes
    //       deppending on the chunk size.

    const size_t nbytes = _cxt->buffer.width() * _cxt->buffer.height() * sizeof(uint32_t);
    cl_int ret = clEnqueueReadBuffer(
      _cl_queue,
      _cl_fb_color,
      true,
      0,
      nbytes,
      _cxt->buffer.pixels(),
      0,
      0,
      nullptr);

    if (ret != CL_SUCCESS) {
      DEBUG_BREAK;
    }

    cl_uint color = 0x10101010;
    clEnqueueFillBuffer(_cl_queue, _cl_fb_color, &color, 4, 0, nbytes, 0, 0, nullptr);
  }

protected:

  bool init_cl();
  bool compile_kernel();
  void log_compile_error();

  // opencl handles
  cl_context _cl_context;
  cl_device_id _cl_device;
  cl_command_queue _cl_queue;

  // kernels
  cl_program _cl_program;
  cl_kernel _cl_kernel;

  // framebuffers
  cl_mem _cl_fb_color;
  cl_mem _cl_fb_depth;

  // triangle list and triangle setup
  cl_mem _cl_triangles;
  cl_mem _cl_triangle_setup;

  gl_context_t *_cxt;
  frame_t _frame;

  // opencl platforms
  std::array<cl_platform_id, 16> _cl_platforms;
};

bool rast_opencl_t::init_cl() {

  cl_int ret = CL_SUCCESS;

  cl_uint num_platforms = 0;
  ret = clGetPlatformIDs(
    _cl_platforms.size(),
    _cl_platforms.data(),
    &num_platforms);
  if (CL_SUCCESS != ret)
    return false;

  ret = clGetDeviceIDs(
    _cl_platforms[0],             // platform selection
    CL_DEVICE_TYPE_CPU,
    1,                            // number of devices
    &_cl_device,                  // device pointer
    nullptr);
  if (CL_SUCCESS != ret)
    return false;

  _cl_context = clCreateContext(
    nullptr,
    1,
    &_cl_device,
    nullptr,
    nullptr,
    nullptr);
  if (!_cl_context) {
    return false;
  }

  _cl_queue = clCreateCommandQueue(
    _cl_context,
    _cl_device,
    cl_command_queue_properties(0),
    nullptr);
  if (!_cl_queue) {
    return false;
  }

  return true;
}

bool rast_opencl_t::compile_kernel() {

  cl_int ret = CL_SUCCESS;

  _cl_program = clCreateProgramWithSource(
    _cl_context,
    1,                            // number of source buffers
    &cl_kernel_raster,            // source code
    nullptr,                      // source length
    nullptr);                     // error code ret
  if (!_cl_program) {
    return false;
  }

  ret = clBuildProgram(
    _cl_program,
    0,                            // num devices
    nullptr,                      // device list
    "-DCHUNK_SIZE=32",            // options
    nullptr,                      // notify callback
    nullptr);                     // user data

  _cl_kernel = clCreateKernel(
    _cl_program,
    "raster",                     // kernel name
    nullptr);
  if (!_cl_kernel) {
    log_compile_error();
    return false;
  }

  return true;
}

void rast_opencl_t::log_compile_error() {
  std::array<char, 8 * 1024> error;
  error[0] = '\0';
  size_t written = 0;
  cl_uint ret = clGetProgramBuildInfo(
    _cl_program,
    _cl_device,
    CL_PROGRAM_BUILD_LOG,
    error.size(),
    error.data(),
    &written);
  printf("%s\n\n", error.data());
}

extern "C" {
__declspec(dllexport) raster_t *raster_create() {
  return new rast_opencl_t;
}

__declspec(dllexport) void raster_release(raster_t *r) {
  delete r;
}
};
