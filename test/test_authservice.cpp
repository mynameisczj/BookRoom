#include "business/authservice.hpp"
#include "core/database/operation_builder.hpp"
#include "core/entities/common.hpp"
#include <gtest/gtest.h>

class AuthServiceTest : public ::testing::Test {
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

  std::vector<std::string> reservation = {"user_id ", "room_id", "reservationStatus", "weekday",
                                          "timeslot"};
  json reservation1 = {{"user_id", 1},
                       {"room_id", 3},
                       {"reservationStatus", ReservationStatus::PENDING},
                       {"weekday", Weekday::Monday},
                       {"timeslot", TimeSlot::Morning}};
  json reservation2 = {{"user_id", 2},
                       {"room_id", 3},
                       {"reservationStatus", ReservationStatus::APPROVED},
                       {"weekday", Weekday::Monday},
                       {"timeslot", TimeSlot::Morning}};
  json reservation3 = {{"user_id", 3},
                       {"room_id", 4},
                       {"reservationStatus", ReservationStatus::PENDING},
                       {"weekday", Weekday::Thursday},
                       {"timeslot", TimeSlot::Afternoon}};
};

TEST_F(AuthServiceTest, TestLogin) {
  {
    JsonDatabase db(test_db_path);
    auto Opbuilder = std::make_shared<OperationBuilder>();
    json result = Opbuilder->create("users", user_columns).execute(db);
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

    AuthService authService(Opbuilder);
    EXPECT_TRUE(authService.login(user1["username"], user1["password"]));
    EXPECT_FALSE(authService.login(user1["username"], user2["password"]));
  }
}