#include "core/database/operation_builder.hpp"

OperationBuilder &OperationBuilder::query() {
  m_operation = "query";
  return *this;
}
OperationBuilder &OperationBuilder::insert(const json &data) {
  m_operation = "insert";
  m_data = data;
  return *this;
}

OperationBuilder &OperationBuilder::update(const json &data, const uint64_t &id) {
  m_operation = "update";
  m_data = data;
  m_id = id;
  return *this;
}

OperationBuilder &OperationBuilder::remove(const uint64_t &id) {
  m_operation = "remove";
  m_id = id;
  return *this;
}

OperationBuilder &OperationBuilder::from(const std::string &tablename) {
  m_tableName = tablename;
  return *this;
}
OperationBuilder &OperationBuilder::where(const json &filter) {
  m_filter = filter;
  return *this;
}
OperationBuilder &OperationBuilder::by(const std::string &colname, const std::string &user) {
  m_filter.value()[colname] = user;
  return *this;
}
OperationBuilder &OperationBuilder::by(const std::string &colname, const uint64_t &id) {
  m_filter.value()[colname] = id;
  return *this;
}

json OperationBuilder::execute(JsonDatabase &db) {
  if (m_operation == "query") {
    return db.query(m_tableName.value(), m_filter.value());
  } else if (m_operation == "insert") {
    bool success = db.insert(m_tableName.value(), m_data.value());
    return json{{"success", success}};
  }
  if (m_operation == "update") {
    bool success = db.update(m_tableName.value(), m_id.value(), m_data.value());
    return json{{"success", success}};
  } else if (m_operation == "remove") {
    bool success = db.remove(m_tableName.value(), m_id.value());
    return json{{"success", success}};
  }
  return {{"Error", "Unexcept Operation"}};
  // Todo::use map to avoid if-else
}