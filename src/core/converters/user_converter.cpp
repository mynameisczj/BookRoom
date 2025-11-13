#include "core/converters/user_converter.hpp"
#include "core/entities/user.hpp"
#include <nlohmann/json.hpp>
#include <vector>
using json = nlohmann::json;

User UserConverter::jsonToUser(const json &) {
  return {};
}
std::vector<User> UserConverter::jsonToUserVector(const json &) {
  return {};
}
json UserConverter::userToJson(const User &) {
  return {};
}
json UserConverter::userVectorToJson(const std::vector<User> &) {
  return {};
}