#pragma once
#include "core/converters/user_converter.hpp"
#include "core/database/operation_builder.hpp"
#include <string>
class AuthService {
private:
  OperationBuilder m_operationBuilder;

public:
  bool login(std::string username, std::string password);
};
