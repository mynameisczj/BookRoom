#include "core/database/jsondb.hpp"
#include "core/entities/common.hpp"
#include <fstream>
#include <gtest/gtest.h>

std::string test_db_path = "test_db.json";

class JsonDataBaseTest : public ::testing::Test {
protected:
  void SetUp() override {
    // 在每个测试开始前执行
  }
  void TearDown() override {
    // 在每个测试结束后执行
  }

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

TEST_F(JsonDataBaseTest, ConstructorAndInit) {
  {
    JsonDatabase db;
    // 应该能正常操作
    EXPECT_TRUE(db.createTable("test_table"));
  }
  {
    JsonDatabase db(test_db_path);
    EXPECT_TRUE(db.createTable("users", user_columns));
    // 文件应该被创建
    }
}
