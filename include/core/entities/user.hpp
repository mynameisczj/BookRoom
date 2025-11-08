#pragma once
#include "common.hpp"
#include <nlohmann/json.hpp>
#include <string>

using json = nlohmann::json;

class User {
private:
  uint64_t m_id;
  std::string m_employeeID;
  std::string m_usrername;
  std::string m_password;
  std::string m_realname;
  UserRole m_role;
};
