#include "core/entities/reservation.hpp"
#include <nlohmann/json.hpp>
#include <vector>
using json = nlohmann::json;
class ReservationConverter {
public:
  static Reservation jsonToReservation(const json &);
  static std::vector<Reservation> jsonToReservationVector(const json &);
  static json reservationToJson(const Reservation &);
  static json reservationVectorToJson(const Reservation &);
};
Reservation ReservationConverter::jsonToReservation(const json &) {
  return {};
}
std::vector<Reservation> ReservationConverter::jsonToReservationVector(const json &) {
  return {};
}
json ReservationConverter::reservationToJson(const Reservation &) {
  return {};
}
json ReservationConverter::reservationVectorToJson(const Reservation &) {
  return {};
}