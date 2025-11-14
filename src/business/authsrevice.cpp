#include "business/authservice.hpp"
AuthService::AuthService(std::shared_ptr<OperationBuilder> userRepo) :
    m_operationBuilder(userRepo) {
}
bool AuthService::login(std::string username, std::string password) {
  return {};
}
