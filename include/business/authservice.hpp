#pragma once
#include "core/converters/user_converter.hpp"
#include "core/database/operation_builder.hpp"
#include <string>
class AuthService {
private:
  std::shared_ptr<OperationBuilder> m_operationBuilder;

public:
  AuthService(std::shared_ptr<OperationBuilder> userRepo);
  bool login(std::string username, std::string password);
};
