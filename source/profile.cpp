#include "profile.h"
#include "context.h"


struct profile_imp_t : public profile_t {

  profile_imp_t()
  {
    reset();
  }

  void on_end_frame() override {
    reset();
  };

  void on_triangles(const std::vector<triangle_t> &t) override {
    _state.triangles += t.size();
  };

protected:

  float _area(const triangle_t &t) const {
    return 1.f;
  }

  void _inspect(const triangle_t &t) {
    // todo: calculate triangle area
    unsigned long area = (unsigned long)_area(t);
    if (area <= 0) {
      return;
    }
    unsigned long index = 0;
    _BitScanReverse(&index, area);
    if (index < 32) {
      _state.bin[index] += 1;
    }
  }

  void reset() {
    memset(&_state, 0, sizeof(_state));
    _state.bin.fill(0);
  }

  struct state_t {
    uint32_t triangles;
    std::array<uint32_t, 32> bin;
  };
  state_t _state;
};

profile_t * profile_create() {
  if (Context) {
    auto &cfg = Context->config;
    bool enable = false;
    if (cfg.get("profile", &enable)) {
      if (enable) {
        return new profile_imp_t;
      }
    }
  }
  return new profile_t;
}
