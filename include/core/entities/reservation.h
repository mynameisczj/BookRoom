#pragma once
#include "common.h"
#include "room.h"
#include "user.h"
#include <nlohmann/json.hpp>

using json = nlohmann::json;

class Reservation {
private:
  User user;
  Room room;
  ReservationStatus reservationStatus;
  Weekday weekday;
  TimeSlot timeslot;
};