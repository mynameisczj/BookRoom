#pragma once
#include "core/converters/room_converter.hpp"
#include "core/database/operation_builder.hpp"
#include "core/entities/common.hpp"

class RoomService {
private:
  std::shared_ptr<OperationBuilder> m_operationBuilder;

public:
  RoomService(std::shared_ptr<OperationBuilder> roomRepo);
  std::vector<Room> getGlobalRoom();
  Room getOneRoom(const uint64_t RoomId);
  bool addRoom(Room room);
  bool deleteRoom(const uint64_t RoomId);
};
