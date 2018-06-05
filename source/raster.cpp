#pragma once
#include <cstdint>
#include <algorithm>

#define WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "raster.h"
#include "math.h"
#include "context.h"


bool raster_load(raster_module_t &dll) {

  const char * dll_name[] = {
    "softgl_rast_wireframe.dll",
    "softgl_rast_reference.dll"
  };

  dll.handle = LoadLibraryA(dll_name[1]);
  if (!dll.handle) {
    return nullptr;
  }

  dll.create = (rast_create_t)GetProcAddress(dll.handle, "raster_create");
  dll.release = (rast_release_t)GetProcAddress(dll.handle, "raster_release");

  if (dll.create && dll.release) {
    dll.inst = dll.create();
    return nullptr != dll.inst;
  }

  return false;
}
