#pragma once
#include "core/converters/user_converter.h"
#include "core/database/operation_builder.h"
#include "core/entities/common.h"
#include "core/entities/user.h"

class UserService {
private:
  OperationBuilder m_operationBuilder;

public:
  std::vector<User> getGlobalUser();
  User getOneUser(const uint64_t userId);
  bool addUser(User user);
  bool deleteUser(const uint64_t userId);
};