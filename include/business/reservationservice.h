#pragma once
#include "core/converters/reservation_converter.h"
#include "core/database/operation_builder.h"
#include "core/entities/common.h"

class ReservationService {
public:
  OperationBuilder m_operationBuilder;

  std::vector<Reservation> getPersonalReservations(uint64_t userId);
  std::vector<Reservation> getGlobalReservations();

  bool requestReservation(uint64_t userId, uint64_t roomId, const Weekday &weekday,
                          const TimeSlot &timeSlot);
  bool cancelReservation(uint64_t reservationId, uint64_t userId);

  bool approveReservation(uint64_t reservationId, const ReservationStatus &reservationStatus);
  ReservationStatus getReservationStatus(uint64_t reservationId);

  bool cleanReservation();
};
