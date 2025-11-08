#pragma once
#include "core/converters/room_converter.hpp"
#include "core/database/operation_builder.hpp"
#include "core/entities/common.hpp"

class RoomService {
private:
  OperationBuilder m_operationBuilder;

public:
  std::vector<Room> getGlobalUser();
  Room getOneUser(const uint64_t RoomId);
  bool addUser(Room room);
  bool deleteUser(const uint64_t RoomId);
};
