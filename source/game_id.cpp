#include <array>
#include <atomic>
#include <cstdint>
#include <cstdio>
#include <memory>

#include <Windows.h>

#include "game_id.h"
#include "log.h"


static uint64_t pearsonHash(const uint8_t *x, size_t len) 
{
  static const std::array<uint8_t, 256> T = {
    // 0-255 shuffled in any (random) order suffices
     98,  6, 85,150, 36, 23,112,164,135,207,169,  5, 26, 64,165,219,
     61, 20, 68, 89,130, 63, 52,102, 24,229,132,245, 80,216,195,115,
     90,168,156,203,177,120,  2,190,188,  7,100,185,174,243,162, 10,
    237, 18,253,225,  8,208,172,244,255,126,101, 79,145,235,228,121,
    123,251, 67,250,161,  0,107, 97,241,111,181, 82,249, 33, 69, 55,
     59,153, 29,  9,213,167, 84, 93, 30, 46, 94, 75,151,114, 73,222,
    197, 96,210, 45, 16,227,248,202, 51,152,252,125, 81,206,215,186,
     39,158,178,187,131,136,  1, 49, 50, 17,141, 91, 47,129, 60, 99,
    154, 35, 86,171,105, 34, 38,200,147, 58, 77,118,173,246, 76,254,
    133,232,196,144,198,124, 53,  4,108, 74,223,234,134,230,157,139,
    189,205,199,128,176, 19,211,236,127,192,231, 70,233, 88,146, 44,
    183,201, 22, 83, 13,214,116,109,159, 32, 95,226,140,220, 57, 12,
    221, 31,209,182,143, 92,149,184,148, 62,113, 65, 37, 27,106,166,
      3, 14,204, 72, 21, 41, 56, 66, 28,193, 40,217, 25, 54,179,117,
    238, 87,240,155,180,170,242,212,191,163, 78,218,137,194,175,110,
     43,119,224, 71,122,142, 42,160,104, 48,247,103, 15, 11,138,239 
  };
  uint64_t out = 0;
  for (size_t j = 0; j < sizeof(out); ++j) {
    uint8_t h = T[(x[0] + j) % 256];
    for (size_t i = 1; i < len; ++i)
       h = T[h ^ x[i]];
    out = (out << 8) | h;
  }
  return out;
}

static uint64_t fileHash(const char *path)
{
  FILE *fd = nullptr;
  if (fopen_s(&fd, path, "rb")) {
    return 0;
  }
  std::unique_ptr<uint8_t[]> temp;
  fseek(fd, 0, SEEK_END);
  size_t size = ftell(fd);
  fseek(fd, 0, SEEK_SET);
  temp = std::make_unique<uint8_t[]>(size);
  fread(temp.get(), 1, 1, fd);
  fclose(fd);
  return pearsonHash(temp.get(), size);
}

game_id_t getGameId()
{
  static std::atomic_bool evaluated = false;
  static game_id_t game_id = e_unknown;
  // early exit if we have already evaluated the game id
  if (evaluated)
    return game_id;
  // we are about to have evaluated
  evaluated = true;
  // space for executable name
  std::array<char, 1024> name;
  // get executable filename
  const DWORD written = GetModuleFileNameA(nullptr, name.data(), name.size());
  if (written == 0 || written >= name.size()) {
      return game_id;
  }
  // force trailing zero
  name[name.size() - 1] = '\0';
  // query list of known hashes
  const uint64_t hash = fileHash(name.data());

  log_t::printf("executable name: %s\n", name.data());
  log_t::printf("executable hash: 0x%llx\n", hash);

  switch (hash) {
  case 0x2365c561bb63848e:
    game_id = e_ut99_goty;
    break;
  case 0x58908a8fe82c5ad4:
    game_id = e_quake_3;
    break;
  case 0xc388218ae8925ad4:
    game_id = e_ut2003_demo;
    break;
  case 0x3b86fbcbf56b79bf:
    game_id = e_half_life_of_demo;
    break;
  default:
    game_id = e_unknown;
  }
  // return known game-id
  return game_id;
}
