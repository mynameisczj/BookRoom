#include "core/entities/user.hpp"
#include <nlohmann/json.hpp>
#include <vector>
using json = nlohmann::json;
class UserConverter {
public:
  static User jsonToUser(const json &);
  static std::vector<User> jsonToUserVector(const json &);
  static json userToJson(const User &);
  static json userVectorToJson(const std::vector<User> &);
};
