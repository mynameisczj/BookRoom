#pragma once

#include "jsondb.hpp"
#include <functional>
#include <nlohmann/json.hpp>
#include <optional>
#include <string>

using json = nlohmann::json;

class OperationBuilder {
private:
  std::optional<std::string> m_tableName;
  std::optional<json> m_filter;
  std::optional<std::string> m_operation;
  std::optional<json> m_data;
  std::optional<uint64_t> m_id;

public:
  OperationBuilder() = default;
  OperationBuilder &insert(const json &data);
  OperationBuilder &update(const json &data, const uint64_t &id);
  OperationBuilder &remove(const uint64_t &id);

  OperationBuilder &query();
  OperationBuilder &from(const std::string &tablename);
  OperationBuilder &where(const json &filter);
  OperationBuilder &by(const std::string &colname, const std::string &user);
  OperationBuilder &by(const std::string &colname, const uint64_t &id);

  json execute(JsonDatabase &db);
};