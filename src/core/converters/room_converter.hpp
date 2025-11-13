#include "core/converters/room_converter.hpp"
#include "core/entities/room.hpp"
#include <nlohmann/json.hpp>
#include <vector>
using json = nlohmann::json;
Room RoomConverter::jsonToRoom(const json &) {
  return {};
}
std::vector<Room> RoomConverter::jsonToRoomVector(const json &) {
  return {};
}
json RoomConverter::roomToJson(const Room &) {
  return {};
}
json RoomConverter::roomVectorToJson(const Room &) {
  return {};
}