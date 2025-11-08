#pragma once
#include "core/converters/room_converter.h"
#include "core/database/operation_builder.h"
#include "core/entities/common.h"

class RoomService {
private:
  OperationBuilder m_operationBuilder;

public:
  std::vector<Room> getGlobalUser();
  Room getOneUser(const uint64_t RoomId);
  bool addUser(Room room);
  bool deleteUser(const uint64_t RoomId);
};
