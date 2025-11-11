#pragma once
#include "core/entities/common.hpp"
#include <string>
class Room {
private:
  std::string m_roomname;
  uint16_t m_capacity;
  bool m_isBook;
  RoomLevel m_level;
};
