#pragma once
#include "common.hpp"
#include "room.hpp"
#include "user.hpp"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Reservation {
public:
  // User m_user;
  // Room m_room;
  uint64_t m_user;
  uint64_t m_room;
  ReservationStatus m_reservationStatus;
  Weekday m_weekday;
  TimeSlot m_timeslot;
  bool operator==(const Reservation &other) const;
};