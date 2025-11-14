#include "business/userservice.hpp"
UserService::UserService(std::shared_ptr<OperationBuilder> userRepo) :
    m_operationBuilder(userRepo) {
}
std::vector<User> UserService::getGlobalUser() {
  return {};
}
User UserService::getOneUser(const uint64_t userId) {
  return {};
}
bool UserService::addUser(User user) {
  return {};
}
bool UserService::deleteUser(const uint64_t userId) {
  return {};
}