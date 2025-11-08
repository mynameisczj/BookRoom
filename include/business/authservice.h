#pragma once
#include "core/converters/user_converter.h"
#include "core/database/operation_builder.h"
#include <string>
class AuthService {
private:
  OperationBuilder m_operationBuilder;

public:
  bool login(std::string username, std::string password);
};
