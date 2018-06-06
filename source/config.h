#pragma once
#include <string>
#include <unordered_map>

struct config_t {

  config_t() = default;

  bool load(const char *path);
  bool save(const char *path);

  bool dump();

  bool clear();

  bool get(const std::string &key, std::string *out);
  bool get(const std::string &key, int32_t *out);
  bool get(const std::string &key, bool *out);
  bool get(const std::string &key, float *out);

  bool set(const std::string &key, const std::string &value);
  bool set(const std::string &key, const int32_t &value);
  bool set(const std::string &key, const bool &value);
  bool set(const std::string &key, const float &value);

protected:
  std::unordered_map<std::string, std::string> map_;
};
