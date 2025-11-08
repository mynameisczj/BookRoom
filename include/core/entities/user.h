#pragma once
#include "common.h"
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class User {
private:
  int id;
  std::string employeeID;
  std::string usrername;
  std::string password;
  std::string realname;
  UserRole role;

public:
  static json userToJson(const User &);
};

json User::userToJson(const User &) {
  return {};
}