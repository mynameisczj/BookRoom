#include "core/entities/room.hpp"
#include <nlohmann/json.hpp>
#include <vector>
using json = nlohmann::json;
class RoomConverter {
public:
  static Room jsonToRoom(const json &);
  static std::vector<Room> jsonToRoomVector(const json &);
  static json roomToJson(const Room &);
  static json roomVectorToJson(const Room &);
};
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