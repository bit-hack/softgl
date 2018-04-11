#pragma once
#include <Windows.h>
#include <cstdint>
#include <memory>

#include "GL.h"

struct gl_state_t {
  GLenum beginMode;
  uint32_t clearColor;
  GLenum cullMode;
};

struct gl_context_t {

  // framebuffer info
  struct buffer_t {
    uint32_t width, height;
    std::unique_ptr<uint32_t[]> pixels;
    std::unique_ptr<float[]> depth;
  };

  // ctor
  gl_context_t(HWND Hwnd, HDC Hdc) : hwnd(Hwnd), hdc(Hdc) {}

  // framebuffer accessors
  buffer_t &frame() { return buffer; }
  const buffer_t &frame() const { return buffer; }

  // resize framebuffer
  void resize(uint32_t w, uint32_t h);

  // get window data
  HWND getHwnd() const { return hwnd; }
  HDC getHdc() const { return hdc; }

  // opengl state machine
  gl_state_t glState;

protected:
  gl_context_t(const gl_context_t &) = delete;

  // framebuffer info
  buffer_t buffer;
  // window data info
  HWND hwnd;
  HDC hdc;
};

// context accessor
gl_context_t *getContext();
#define Context getContext()

namespace {
inline gl_state_t &getGLState() {
  return getContext()->glState;
}
} // namespace {}

#define GLState getGLState()
