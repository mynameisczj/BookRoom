#include "core/converters/reservation_converter.hpp"
#include "core/converters/room_converter.hpp"
#include "core/converters/user_converter.hpp"
#include "core/entities/reservation.hpp"
#include "core/entities/room.hpp"
#include "core/entities/user.hpp"
#include <gtest/gtest.h>

class ConventerTest : public ::testing::Test {
protected:
  void SetUp() override {
  }
  void TearDown() override {
  }

  // 测试数据
  json jsonUser1 = {{"id", 1},
                    {"employeeID", "1001"},
                    {"username", "Dolores"},
                    {"password", 142857},
                    {"realname", "TrueDolores"},
                    {"role", UserRole::RESEARCHER}};
  json jsonUser2 = {{"id", 2},
                    {"employeeID", "1002"},
                    {"username", "leetcode"},
                    {"password", 222222},
                    {"realname", "Trueleetcode"},
                    {"role", UserRole::ADMIN_STAFF}};
  json jsonUser3 = {{"id", 3},
                    {"employeeID", "1003"},
                    {"username", "luogu"},
                    {"password", 222222},
                    {"realname", "Trueluogu"},
                    {"role", UserRole::SYSTEM_ADMIN}};

  json jsonRoom1 = {{"id", 1},
                    {"roomname", "abcd"},
                    {"capacity", 100},
                    {"isBook", true},
                    {"level", RoomLevel::Level_1}};
  json jsonRoom2 = {{"id", 2},
                    {"roomname", "aabb"},
                    {"capacity", 200},
                    {"isBook", false},
                    {"level", RoomLevel::Level_1}};
  json jsonRoom3 = {{"id", 3},
                    {"roomname", "cdef"},
                    {"capacity", 300},
                    {"isBook", false},
                    {"level", RoomLevel::Level_2}};
  json jsonReservation1 = {{"id", 1},
                           {"user_id", 1},
                           {"room_id", 3},
                           {"reservationStatus", ReservationStatus::PENDING},
                           {"weekday", Weekday::Monday},
                           {"timeslot", TimeSlot::Morning}};
  json jsonReservation2 = {{"id", 2},
                           {"user_id", 2},
                           {"room_id", 3},
                           {"reservationStatus", ReservationStatus::APPROVED},
                           {"weekday", Weekday::Monday},
                           {"timeslot", TimeSlot::Morning}};
  json jsonReservation3 = {{"id", 3},
                           {"user_id", 3},
                           {"room_id", 4},
                           {"reservationStatus", ReservationStatus::PENDING},
                           {"weekday", Weekday::Thursday},
                           {"timeslot", TimeSlot::Afternoon}};
};
TEST_F(ConventerTest, UserConverter) {
  {
    User user1 = UserConverter::jsonToUser(jsonUser1);
    EXPECT_EQ(user1.m_employeeID, jsonUser1["employeeID"]);
    EXPECT_EQ(user1.m_password, jsonUser1["password"]);
    EXPECT_EQ(user1.m_realname, jsonUser1["realname"]);
    EXPECT_EQ(user1.m_username, jsonUser1["username"]);
    EXPECT_EQ(user1.m_role, jsonUser1["role"]);
  }
  {
    User user1 = UserConverter::jsonToUser(jsonUser1);
    json result = UserConverter::userToJson(user1);
    EXPECT_EQ(result, jsonUser1);
  }
  {
    json jsonUserVector;
    jsonUserVector.push_back(jsonUser1);
    jsonUserVector.push_back(jsonUser2);
    jsonUserVector.push_back(jsonUser3);
    std::vector<User> userVector{};
    userVector = UserConverter::jsonToUserVector(jsonUserVector);
    User user1 = UserConverter::jsonToUser(jsonUser1);
    User user2 = UserConverter::jsonToUser(jsonUser2);
    User user3 = UserConverter::jsonToUser(jsonUser3);
    if (userVector.size()) {
      EXPECT_EQ(user1, userVector[0]);
      EXPECT_EQ(user2, userVector[1]);
      EXPECT_EQ(user3, userVector[2]);
    } else {
      EXPECT_TRUE(false);
    }
  }
  {
    json jsonUserVector;
    jsonUserVector.push_back(jsonUser1);
    jsonUserVector.push_back(jsonUser2);
    jsonUserVector.push_back(jsonUser3);
    std::vector<User> userVector{};
    userVector = UserConverter::jsonToUserVector(jsonUserVector);
    EXPECT_EQ(jsonUserVector, UserConverter::userVectorToJson(userVector));
  }
}

TEST_F(ConventerTest, RoomConverter) {
  {
    Room room1 = RoomConverter::jsonToRoom(jsonRoom1);
    EXPECT_EQ(room1.m_capacity, jsonRoom1["capacity"]);
    EXPECT_EQ(room1.m_isBook, jsonRoom1["isBook"]);
    EXPECT_EQ(room1.m_level, jsonRoom1["level"]);
    EXPECT_EQ(room1.m_roomname, jsonRoom1["roomname"]);
  }
  {
    Room room1 = RoomConverter::jsonToRoom(jsonRoom1);
    json result = RoomConverter::roomToJson(room1);
    EXPECT_EQ(result, jsonRoom1);
  }
  {
    json jsonRoomVector;
    jsonRoomVector.push_back(jsonRoom1);
    jsonRoomVector.push_back(jsonRoom2);
    jsonRoomVector.push_back(jsonRoom3);
    std::vector<Room> roomVector{};
    roomVector = RoomConverter::jsonToRoomVector(jsonRoomVector);
    Room room1 = RoomConverter::jsonToRoom(jsonRoom1);
    Room room2 = RoomConverter::jsonToRoom(jsonRoom2);
    Room room3 = RoomConverter::jsonToRoom(jsonRoom3);
    if (roomVector.size()) {
      EXPECT_EQ(room1, roomVector[0]);
      EXPECT_EQ(room2, roomVector[1]);
      EXPECT_EQ(room3, roomVector[2]);
    } else {
      EXPECT_TRUE(false);
    }
  }
  {
    json jsonRoomVector;
    jsonRoomVector.push_back(jsonRoom1);
    jsonRoomVector.push_back(jsonRoom2);
    jsonRoomVector.push_back(jsonRoom3);
    std::vector<Room> roomVector{};
    roomVector = RoomConverter::jsonToRoomVector(jsonRoomVector);
    EXPECT_EQ(jsonRoomVector, RoomConverter::roomVectorToJson(roomVector));
  }
}

TEST_F(ConventerTest, ReservationConverter) {
  {
    Reservation reservation1 = ReservationConverter::jsonToReservation(jsonReservation1);
    EXPECT_EQ(reservation1.m_reservationStatus, jsonReservation1["reservationStatus"]);
    EXPECT_EQ(reservation1.m_room, jsonReservation1["room"]);
    EXPECT_EQ(reservation1.m_timeslot, jsonReservation1["timeslot"]);
    EXPECT_EQ(reservation1.m_weekday, jsonReservation1["weekday"]);
    EXPECT_EQ(reservation1.m_user, jsonReservation1["user"]);
  }
  {
    Reservation reservation1 = ReservationConverter::jsonToReservation(jsonReservation1);
    json result = ReservationConverter::reservationToJson(reservation1);
    EXPECT_EQ(result, jsonReservation1);
  }
  {
    json jsonReservationVector;
    jsonReservationVector.push_back(jsonReservation1);
    jsonReservationVector.push_back(jsonReservation2);
    jsonReservationVector.push_back(jsonReservation3);
    std::vector<Reservation> reservationVector{};
    reservationVector = ReservationConverter::jsonToReservationVector(jsonReservationVector);
    Reservation reservation1 = ReservationConverter::jsonToReservation(jsonReservation1);
    Reservation reservation2 = ReservationConverter::jsonToReservation(jsonReservation2);
    Reservation reservation3 = ReservationConverter::jsonToReservation(jsonReservation3);
    if (reservationVector.size()) {
      EXPECT_EQ(reservation1, reservationVector[0]);
      EXPECT_EQ(reservation2, reservationVector[1]);
      EXPECT_EQ(reservation3, reservationVector[2]);
    } else {
      EXPECT_TRUE(false);
    }
  }
  {
    json jsonReservationVector;
    jsonReservationVector.push_back(jsonReservation1);
    jsonReservationVector.push_back(jsonReservation2);
    jsonReservationVector.push_back(jsonReservation3);
    std::vector<Reservation> reservationVector{};
    reservationVector = ReservationConverter::jsonToReservationVector(jsonReservationVector);
    EXPECT_EQ(jsonReservationVector,
              ReservationConverter::reservationVectorToJson(reservationVector));
  }
}