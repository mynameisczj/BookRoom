#include "business/roomservice.hpp"
RoomService::RoomService(std::shared_ptr<OperationBuilder> roomRepo) :
    m_operationBuilder(roomRepo) {
}
std::vector<Room> RoomService::getGlobalRoom() {
  return {};
}
Room RoomService::getOneRoom(const uint64_t RoomId) {
  return {};
}
bool RoomService::addRoom(Room room) {
  return {};
}
bool RoomService::deleteRoom(const uint64_t RoomId) {
  return {};
}