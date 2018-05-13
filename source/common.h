#pragma once
#include <cstdint>


// a simple break once macro
#if _DEBUG
#define DEBUG_BREAK                 \
  {                                 \
    static bool once=true;          \
    if (once) {                     \
      __debugbreak();               \
      once = false;                 \
      printf("%s\n", __FUNCTION__); \
    }                               \
  }
#else
#define DEBUG_BREAK
#endif


void save_bmp(const uint32_t *pixels, uint32_t w, uint32_t h, const char *path);
