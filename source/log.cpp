#include "log.h"
#include "context.h"

FILE *log_t::_fd;

void log_t::_open_fd() {
  if (!_fd) {
    _fd = fopen("softgl.log", "w");
  }
}

void log_t::_reopen_stdio() {
  if (Context) {
    bool enable = false;
    Context->config.get("open_stdio", &enable);
    if (enable) {
      AllocConsole();
      freopen("CONOUT$", "wt", stdout);
    }
  }
}
