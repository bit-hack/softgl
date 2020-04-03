#pragma once
#include <cstdint>
#include <algorithm>

#include "raster.h"
#include "math.h"
#include "context.h"


bool raster_load(raster_module_t &dll, gl_context_t &cxt) {

  const char * dll_name[] = {
    "softgl_rast_wireframe.dll",
    "softgl_rast_reference.dll"
  };

  std::string name;
  if (!cxt.config.get("raster_dll", &name)) {
    name = dll_name[0];
  }

  dll.handle = LoadLibraryA(name.c_str());
  if (!dll.handle) {
    return false;
  }

  dll.create = (rast_create_t)GetProcAddress(dll.handle, "raster_create");
  dll.release = (rast_release_t)GetProcAddress(dll.handle, "raster_release");

  if (dll.create && dll.release) {
    dll.inst = dll.create();
    return nullptr != dll.inst;
  }

  return false;
}
