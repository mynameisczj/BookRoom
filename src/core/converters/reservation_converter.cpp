#include "core/converters/reservation_converter.hpp"
#include "core/entities/reservation.hpp"
#include <nlohmann/json.hpp>
#include <vector>
using json = nlohmann::json;

Reservation ReservationConverter::jsonToReservation(const json &) {
  return {};
}
std::vector<Reservation> ReservationConverter::jsonToReservationVector(const json &) {
  return {};
}
json ReservationConverter::reservationToJson(const Reservation &) {
  return {};
}
json ReservationConverter::reservationVectorToJson(const std::vector<Reservation> &) {
  return {};
}