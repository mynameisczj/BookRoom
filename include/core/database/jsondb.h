#pragma once

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class JsonDatabase {
private:
  bool loadFromFile();
  bool saveToFile();
  void init();

public:
  JsonDatabase(const std::string &_filename = "data.json") : filename(_filename) {
    init();
  }
  JsonDatabase(const JsonDatabase &) = delete;
  JsonDatabase &operator=(const JsonDatabase &) = delete;
  ~JsonDatabase() = default;

  bool createTable(const std::string &tableName, const std::vector<std::string> &columns = {});
  uint64_t insert(const std::string &tableName, const json &record);
  bool remove(const std::string &tableName, uint64_t id);
  json query(const std::string &tableName, const json &filter);
  bool update(const std::string &tableName, uint64_t id, const json &updates);

private:
  json jsondata;
  std::string filename;
};