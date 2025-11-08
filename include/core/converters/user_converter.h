#include "core/entities/user.h"
#include <nlohmann/json.hpp>
#include <vector>
using json = nlohmann::json;
class UserConverter {
public:
  static User jsonToUser(const json &);
  static std::vector<User> jsonToUserVector(const json &);
  static json UserToJson(const User &);
  static json UserVectorToJson(const User &);
};
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