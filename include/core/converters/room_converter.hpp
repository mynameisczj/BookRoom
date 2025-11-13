#include "core/entities/room.hpp"
#include <nlohmann/json.hpp>
#include <vector>
using json = nlohmann::json;
class RoomConverter {
public:
  static Room jsonToRoom(const json &);
  static std::vector<Room> jsonToRoomVector(const json &);
  static json roomToJson(const Room &);
  static json roomVectorToJson(const std::vector<Room> &);
};
