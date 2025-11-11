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
  std::unordered_map<std::string, uint64_t> m_tableIDCounters;

public:
  JsonDatabase(const std::string &_filename = "data.json") : m_filename(_filename) {
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
  json m_jsondata;
  std::string m_filename;
};