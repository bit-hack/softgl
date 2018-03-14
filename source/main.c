#include "gl_func_enum.h"
#include <Windows.h>
#include <stdbool.h>

extern const char *gl_func_names[];
extern void *gl_func_table[];

static HMODULE opengl_dll = INVALID_HANDLE_VALUE;

bool init_gl_func_table() {
  if (opengl_dll == INVALID_HANDLE_VALUE) {
#if 1
    // remove the current directory from the search order
    SetDllDirectoryA(NULL);
    opengl_dll =
        LoadLibraryExA("C:\\Windows\\System32\\opengl32.dll", NULL, LOAD_WITH_ALTERED_SEARCH_PATH);
#else
    // search for OPENGL32 in system32
    opengl_dll =
        LoadLibraryExA("OPENGL32.dll", NULL, LOAD_LIBRARY_SEARCH_SYSTEM32);
#endif
  }

  if (opengl_dll == INVALID_HANDLE_VALUE) {
    return false;
  }

  if (gl_func_table[e_glFlush] != 0) {
    return true;
  }

  // import all OpenGL 1.1 functions
  for (int i = 0; i < e_gl_func_count__; ++i) {
    const char *gl_func = gl_func_names[i];
    if (gl_func_table[i]) {
      continue;
    }
    gl_func_table[i] = GetProcAddress(opengl_dll, gl_func);
    if (!gl_func_table[i]) {
      // unable to locate opengl export
      continue;
    }
  }

  return true;
}

LONG CALLBACK VectoredHandler(_In_ PEXCEPTION_POINTERS ExceptionInfo) {
  return EXCEPTION_CONTINUE_SEARCH;
}

BOOL WINAPI DllMain(_In_ HINSTANCE hinstDLL, _In_ DWORD fdwReason,
                    _In_ LPVOID lpvReserved) {

  // add vectored exception handler
  if (!AddVectoredExceptionHandler(1, VectoredHandler)) {
  }

  return TRUE;
}
