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
json UserConverter::UserToJson(const User &) {
  return {};
}
json UserConverter::UserVectorToJson(const User &) {
  return {};
}