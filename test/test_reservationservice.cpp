#include "business/reservationservice.hpp"
#include "core/database/operation_builder.hpp"
#include "core/entities/common.hpp"
#include <gtest/gtest.h>

class ReservationServiceTest : public ::testing::Test {
protected:
  void SetUp() override {
    removeTestFile();
  }

  void TearDown() override {
    removeTestFile();
  }

  bool testFileExists() const {
    std::ifstream file(test_db_path);
    return file.good();
  }

  void removeTestFile() {
    std::remove(test_db_path.c_str());
  }

  std::string test_db_path = "test_db.json";
  // 测试数据
  std::vector<std::string> user_columns = {"employeeID ", "username", "password", "realname",
                                           "Role"};
  json user1 = {{"employeeID", "1001"},
                {"username", "Dolores"},
                {"password", 142857},
                {"realname", "TrueDolores"},
                {"Role", UserRole::RESEARCHER}};
  json user2 = {{"employeeID", "1002"},
                {"username", "leetcode"},
                {"password", 222222},
                {"realname", "Trueleetcode"},
                {"Role", UserRole::ADMIN_STAFF}};
  json user3 = {{"employeeID", "1003"},
                {"username", "luogu"},
                {"password", 222222},
                {"realname", "Trueluogu"},
                {"Role", UserRole::SYSTEM_ADMIN}};
  json user1findTrue = {
      {"employeeID", "1001"},
      {"username", "Dolores"},
  };
  json user2findTrue = {
      {"employeeID", "1002"},
      {"username", "leetcode"},
  };
  json user3findTrue = {
      {"employeeID", "1003"},
      {"username", "luogu"},
  };
  json user3findFalse = {
      {"employeeID", "1002"},
      {"username", "luogu"},
  };
  json user3Update = {
      {"employeeID", "1002"},
      {"username", "Newluogu"},
      {"password", 333333},
  };
  std::vector<std::string> room_columns = {"roomname", "capacity", "isBook"};
  json room1 = {{"roomname", "abcd"},
                {"capacity", 100},
                {"isBook", true},
                {"level", RoomLevel::Level_1}};
  json room2 = {{"roomname", "aabb"},
                {"capacity", 200},
                {"isBook", false},
                {"level", RoomLevel::Level_1}};
  json room3 = {{"roomname", "cdef"},
                {"capacity", 300},
                {"isBook", false},
                {"level", RoomLevel::Level_2}};

  std::vector<std::string> reservation_colnums = {"user_id ", "room_id", "reservationStatus",
                                                  "weekday", "timeslot"};
  json reservation1 = {{"user_id", 1},
                       {"room_id", 3},
                       {"reservationStatus", ReservationStatus::PENDING},
                       {"weekday", Weekday::Monday},
                       {"timeslot", TimeSlot::Morning}};
  json reservation2 = {{"user_id", 1},
                       {"room_id", 2},
                       {"reservationStatus", ReservationStatus::APPROVED},
                       {"weekday", Weekday::Monday},
                       {"timeslot", TimeSlot::Morning}};
  json reservation3 = {{"user_id", 3},
                       {"room_id", 4},
                       {"reservationStatus", ReservationStatus::PENDING},
                       {"weekday", Weekday::Thursday},
                       {"timeslot", TimeSlot::Afternoon}};
};
TEST_F(ReservationServiceTest, TestGetGobalReservation) {
  {
    JsonDatabase db(test_db_path);
    auto Opbuilder = std::make_shared<OperationBuilder>();
    json result = Opbuilder->create("reservations", reservation_colnums).execute(db);
    Opbuilder->reset();
    result = Opbuilder->from("reservation").insert(reservation1).execute(db);
    EXPECT_EQ(result["success"], true);
    Opbuilder->reset();
    result = Opbuilder->from("reservation").insert(reservation2).execute(db);
    EXPECT_EQ(result["success"], true);
    Opbuilder->reset();
    result = Opbuilder->from("reservation").insert(reservation3).execute(db);
    EXPECT_EQ(result["success"], true);
    Opbuilder->reset();

    result = Opbuilder->from("reservation").query().execute(db);
    ReservationService reservationService(Opbuilder);
    std::vector<Reservation> vectorresult1 = ReservationConverter::jsonToReservationVector(result);
    std::vector<Reservation> vectorresult2 = reservationService.getGlobalReservations();
    if (vectorresult1.size() && vectorresult2.size()) {
      EXPECT_EQ(vectorresult1[0], vectorresult2[0]);
      EXPECT_EQ(vectorresult1[1], vectorresult2[1]);
      EXPECT_EQ(vectorresult1[2], vectorresult2[2]);
    } else {
      EXPECT_TRUE(false);
    }
  }
}
TEST_F(ReservationServiceTest, TestClean) {
  {
    JsonDatabase db(test_db_path);
    auto Opbuilder = std::make_shared<OperationBuilder>();
    json result = Opbuilder->create("reservations", reservation_colnums).execute(db);
    Opbuilder->reset();
    result = Opbuilder->from("reservation").insert(reservation1).execute(db);
    EXPECT_EQ(result["success"], true);
    Opbuilder->reset();
    result = Opbuilder->from("reservation").insert(reservation2).execute(db);
    EXPECT_EQ(result["success"], true);
    Opbuilder->reset();
    result = Opbuilder->from("reservation").insert(reservation3).execute(db);
    EXPECT_EQ(result["success"], true);
    Opbuilder->reset();

    result = Opbuilder->from("reservation").query().execute(db);
    ReservationService reservationService(Opbuilder);
    std::vector<Reservation> vectorresult1 = ReservationConverter::jsonToReservationVector(result);
    std::vector<Reservation> vectorresult2 = reservationService.getGlobalReservations();
    if (vectorresult1.size() && vectorresult2.size()) {
      EXPECT_EQ(vectorresult1[0], vectorresult2[0]);
      EXPECT_EQ(vectorresult1[1], vectorresult2[1]);
      EXPECT_EQ(vectorresult1[2], vectorresult2[2]);
    } else {
      EXPECT_TRUE(false);
    }
    EXPECT_TRUE(reservationService.cleanReservation());
    vectorresult2 = reservationService.getGlobalReservations();
    EXPECT_TRUE(vectorresult2.empty());
  }
}

TEST_F(ReservationServiceTest, TestGetPersonalReservations) {
  {
    JsonDatabase db(test_db_path);
    auto Opbuilder = std::make_shared<OperationBuilder>();
    json result = Opbuilder->create("reservations", reservation_colnums).execute(db);
    Opbuilder->reset();
    result = Opbuilder->from("reservation").insert(reservation1).execute(db);
    EXPECT_EQ(result["success"], true);
    Opbuilder->reset();
    result = Opbuilder->from("reservation").insert(reservation2).execute(db);
    EXPECT_EQ(result["success"], true);
    Opbuilder->reset();
    result = Opbuilder->from("reservation").insert(reservation3).execute(db);
    EXPECT_EQ(result["success"], true);
    Opbuilder->reset();

    Opbuilder->reset();
    result = Opbuilder->from("user").insert(user1).execute(db);
    EXPECT_EQ(result["success"], true);
    EXPECT_EQ(result["id"], db.query("users", user1findTrue)["id"]);
    Opbuilder->reset();
    result = Opbuilder->from("user").insert(user2).execute(db);
    EXPECT_EQ(result["success"], true);
    Opbuilder->reset();
    result = Opbuilder->from("user").insert(user3).execute(db);
    EXPECT_EQ(result["success"], true);

    ReservationService reservationService(Opbuilder);
    std::vector<Reservation> vectorresult2 =
        reservationService.getPersonalReservations(db.query("users", user1findTrue)["id"]);
    if (vectorresult2.size()) {
      EXPECT_EQ(vectorresult2.size(), 2);
      EXPECT_EQ(vectorresult2[0].m_user, db.query("users", user1findTrue)["id"]);
    } else {
      EXPECT_TRUE(false);
    }
  }
}

TEST_F(ReservationServiceTest, TestRequestReservation) {
  {
    JsonDatabase db(test_db_path);
    auto Opbuilder = std::make_shared<OperationBuilder>();
    ReservationService reservationService(Opbuilder);
    json result = Opbuilder->create("reservations", reservation_colnums).execute(db);
    Opbuilder->reset();

    Reservation re1 = ReservationConverter::jsonToReservation(reservation1);
    reservationService.requestReservation(re1.m_user, re1.m_room, re1.m_weekday, re1.m_timeslot);
    Opbuilder->reset();
    result = Opbuilder->from("reservation")
                 .query()
                 .by("user_id", reservation1["user_id"].get<uint64_t>())
                 .execute(db);
    EXPECT_EQ(reservation1, result);
  }
}
TEST_F(ReservationServiceTest, TestCancelReservation) {
  {
    JsonDatabase db(test_db_path);
    auto Opbuilder = std::make_shared<OperationBuilder>();
    ReservationService reservationService(Opbuilder);
    json result = Opbuilder->create("reservations", reservation_colnums).execute(db);
    Opbuilder->reset();
    result = Opbuilder->from("reservation").insert(reservation1).execute(db);
    EXPECT_EQ(result["success"], true);
    Opbuilder->reset();
    result = Opbuilder->from("reservation")
                 .query()
                 .by("user_id", reservation1["user_id"].get<uint64_t>())
                 .execute(db);
    uint64_t res1ID = result["id"];
    EXPECT_TRUE(reservationService.cancelReservation(res1ID, reservation1["user_id"]));
    result = Opbuilder->from("reservation")
                 .query()
                 .by("user_id", reservation1["user_id"].get<uint64_t>())
                 .execute(db);
    EXPECT_TRUE(result.empty());
  }
}
TEST_F(ReservationServiceTest, TestApproveReservation) {
  {
    JsonDatabase db(test_db_path);
    auto Opbuilder = std::make_shared<OperationBuilder>();
    ReservationService reservationService(Opbuilder);
    json result = Opbuilder->create("reservations", reservation_colnums).execute(db);
    Opbuilder->reset();
    result = Opbuilder->from("reservation").insert(reservation1).execute(db);
    EXPECT_EQ(result["success"], true);
    Opbuilder->reset();
    result = Opbuilder->from("reservation")
                 .query()
                 .by("user_id", reservation1["user_id"].get<uint64_t>())
                 .execute(db);
    uint64_t res1ID = result["id"];
    EXPECT_EQ(result["reservationStatus"], reservation1["reservationStatus"]);

    EXPECT_TRUE(reservationService.approveReservation(res1ID, ReservationStatus::APPROVED));
    Opbuilder->reset();
    result = Opbuilder->from("reservation")
                 .query()
                 .by("user_id", reservation1["user_id"].get<uint64_t>())
                 .execute(db);
    EXPECT_EQ(result["reservationStatus"], ReservationStatus::APPROVED);
  }
}