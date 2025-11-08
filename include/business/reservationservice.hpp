#pragma once
#include "core/converters/reservation_converter.hpp"
#include "core/database/operation_builder.hpp"
#include "core/entities/common.hpp"

class ReservationService {
private:
  OperationBuilder m_operationBuilder;

public:
  std::vector<Reservation> getPersonalReservations(uint64_t userId);
  std::vector<Reservation> getGlobalReservations();

  bool requestReservation(uint64_t userId, uint64_t roomId, const Weekday &weekday,
                          const TimeSlot &timeSlot);
  bool cancelReservation(uint64_t reservationId, uint64_t userId);

  bool approveReservation(uint64_t reservationId, const ReservationStatus &reservationStatus);
  ReservationStatus getReservationStatus(uint64_t reservationId);

  bool cleanReservation();
};
