#include "business/reservationservice.h"
#include "core/database/operation_builder.h"
#include "core/entities/common.h"
#include <vector>

std::vector<Reservation> ReservationService::getPersonalReservations(uint64_t userId) {
  return {};
}
std::vector<Reservation> ReservationService::getGlobalReservations() {
  return {};
}

bool ReservationService::requestReservation(uint64_t userId, uint64_t roomId,
                                            const Weekday &weekday, const TimeSlot &timeSlot) {
  return {};
}
bool ReservationService::cancelReservation(uint64_t reservationId, uint64_t userId) {
  return {};
}

bool ReservationService::approveReservation(uint64_t reservationId,
                                            const ReservationStatus &reservationStatus) {
  return {};
}
ReservationStatus ReservationService::getReservationStatus(uint64_t reservationId) {
  return {};
}

bool ReservationService::cleanReservation() {
  return {};
}