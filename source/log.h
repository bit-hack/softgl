#pragma once
#include <cstdarg>
#include <cstdio>
#include <cstring>

#include "windows.h"

struct log_t {

  static FILE *_fd;

  static void _open_fd();

  static void _reopen_stdio();

  static void printf(const char *fmt, ...) {
    va_list ap;
    {
      va_start(ap, fmt);
      _open_fd();
      if (_fd) {
        vfprintf(_fd, fmt, ap);
        fflush(_fd);
      }
      va_end(ap);
    }
    {
      va_start(ap, fmt);
      vprintf(fmt, ap);
      va_end(ap);
    }
  }
};
