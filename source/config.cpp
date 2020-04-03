#include <stdio.h>

#include "config.h"


static bool extract(const char *line, std::string &key, std::string &value) {
  // clear output strings
  key.clear(), value.clear();
  // parse head
  const char *p = line;
  // skip whitespace
  while (*p == ' ' || *p == '\t' || *p == '\r')
    ++p;
  // check for comments
  if (*p == '#') {
    return false;
  }
  const char *k1 = p;
  while (*p > ' ')
    ++p;
  if (k1 != p) {
    key.assign(k1, p);
  }
  // value
  while (*p == ' ' || *p == '\t' || *p == '\r')
    ++p;
  const char *v1 = p;
  if (*p == '"' ? ++p, ++v1, true : false) {
    while (*p != '"' && (*p >= ' ' || *p == '\t'))
      ++p;
  } else {
    while (*p > ' ')
      ++p;
  }
  if (v1 != p) {
    value.assign(v1, p);
  }
  // should have got something for both
  return !key.empty() && !value.empty();
}

bool config_t::load(const char *path) {
  if (!path)
    return false;
  FILE *fp = fopen(path, "r");
  if (!fp)
    return false;
  char line[1024];
  std::string key, value;
  while (!feof(fp)) {
    if (!fgets(line, sizeof(line), fp)) {
      break;
    }
    line[sizeof(line) - 1] = '\0';
    if (extract(line, key, value)) {
      map_[key] = value;
    }
  }
  fclose(fp);
  return true;
}

bool config_t::save(const char *path) {
  if (!path)
    return false;
  FILE *fp = fopen(path, "w");
  if (!fp)
    return false;
  for (const auto &a : map_) {
    fprintf(fp, "%s %s\n", a.first.c_str(), a.second.c_str());
  }
  fclose(fp);
  return true;
}

bool config_t::clear() {
  map_.clear();
  return false;
}

bool config_t::get(const std::string &key, std::string *out) {
  auto itt = map_.find(key);
  if (itt != map_.end()) {
    *out = itt->second;
    return true;
  }
  return false;
}

bool config_t::get(const std::string &key, int32_t *out) {
  auto itt = map_.find(key);
  if (itt != map_.end()) {
    const std::string &val = itt->second;
    if (sscanf(val.c_str(), "%d", out) == 1)
      return true;
  }
  return false;
}

bool config_t::get(const std::string &key, bool *out) {
  auto itt = map_.find(key);
  bool ret = false;
  if (itt != map_.end()) {
    const std::string &val = itt->second;
    if (val == "True" || val == "true")
      *out = true, ret = true;
    if (val == "False" || val == "false")
      *out = false, ret = true;
  }
  return ret;
}

bool config_t::get(const std::string &key, float *out) {
  auto itt = map_.find(key);
  if (itt != map_.end()) {
    const std::string &val = itt->second;
    if (sscanf(val.c_str(), "%f", out) == 1)
      return true;
  }
  return false;
}

bool config_t::set(const std::string &key, const std::string &value) {
  map_[key] = value;
  return true;
}

bool config_t::set(const std::string &key, const int32_t &value) {
  map_[key] = std::to_string(value);
  return true;
}

bool config_t::set(const std::string &key, const bool &value) {
  map_[key] = std::to_string(value);
  return true;
}

bool config_t::set(const std::string &key, const float &value) {
  map_[key] = std::to_string(value);
  return true;
}

bool config_t::dump() {
  for (auto itt : map_) {
    printf("%s %s\n", itt.first.c_str(), itt.second.c_str());
  }
  return true;
}
