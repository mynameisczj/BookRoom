#include "core/database/jsondb.hpp"

bool JsonDatabase::loadFromFile() {
  return {};
}
bool JsonDatabase::saveToFile() {
  return {};
}
void JsonDatabase::init() {
}

bool JsonDatabase::createTable(const std::string &tableName,
                               const std::vector<std::string> &columns) {
  return {};
}
uint64_t JsonDatabase::insert(const std::string &tableName, const json &record) {
  return {};
}
bool JsonDatabase::remove(const std::string &tableName, uint64_t id) {
  return {};
}
json JsonDatabase::query(const std::string &tableName, const json &filter) {
  return {};
}
bool JsonDatabase::update(const std::string &tableName, uint64_t id, const json &updates) {
  return {};
}