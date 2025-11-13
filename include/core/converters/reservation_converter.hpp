#include "core/entities/reservation.hpp"
#include <nlohmann/json.hpp>
#include <vector>
using json = nlohmann::json;
class ReservationConverter {
public:
  static Reservation jsonToReservation(const json &);
  static std::vector<Reservation> jsonToReservationVector(const json &);
  static json reservationToJson(const Reservation &);
  static json reservationVectorToJson(const std::vector<Reservation> &);
};
