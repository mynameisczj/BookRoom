#pragma once
#include "core/converters/user_converter.hpp"
#include "core/database/operation_builder.hpp"
#include "core/entities/common.hpp"
#include "core/entities/user.hpp"

class UserService {
private:
  OperationBuilder m_operationBuilder;

public:
  std::vector<User> getGlobalUser();
  User getOneUser(const uint64_t userId);
  bool addUser(User user);
  bool deleteUser(const uint64_t userId);
};