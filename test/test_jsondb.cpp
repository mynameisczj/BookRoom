#include "core/database/jsondb.hpp"
#include "core/entities/common.hpp"
#include <cstdio>
#include <fstream>
#include <gtest/gtest.h>

class JsonDataBaseTest : public ::testing::Test {
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

TEST_F(JsonDataBaseTest, FileCreation) {
  {
    EXPECT_FALSE(testFileExists());
    JsonDatabase db(test_db_path);
    EXPECT_TRUE(db.createTable("users", user_columns));
    EXPECT_TRUE(testFileExists());
  }
}
TEST_F(JsonDataBaseTest, InsertAndQuery) {
  {
    JsonDatabase db(test_db_path);
    db.createTable("users", user_columns);
    uint64_t user1ID = db.insert("users", user1);
    EXPECT_EQ(user1ID, db.query("users", user1findTrue)["id"]);
  }
  EXPECT_TRUE(testFileExists());
  {
    JsonDatabase db(test_db_path);
    json result = db.query("users", json::object());
    EXPECT_FALSE(result.empty());
  }
  {
    JsonDatabase db(test_db_path);
    json result = db.query("users", json::object());
    EXPECT_FALSE(db.insert("users", user1));

    db.insert("users", user2);
    db.insert("users", user3);
    result = db.query("users", user1findTrue);
    EXPECT_EQ(result["username"], user1findTrue["username"]);
    result = db.query("users", user2findTrue);
    EXPECT_EQ(result["username"], user2findTrue["username"]);
    result = db.query("users", user3findFalse);
    EXPECT_TRUE(result.empty());
  }
}
TEST_F(JsonDataBaseTest, RemoveAndInsert) {
  {
    JsonDatabase db(test_db_path);
    EXPECT_TRUE(db.createTable("users", user_columns));
    uint64_t user1ID = db.insert("users", user1);
    EXPECT_FALSE(db.insert("users", user1));
    EXPECT_TRUE(db.remove("users", user1ID));
    EXPECT_FALSE(db.remove("users", user1ID));
  }
}
TEST_F(JsonDataBaseTest, UpdateAndInsert) {
  {
    JsonDatabase db(test_db_path);
    EXPECT_TRUE(db.createTable("users", user_columns));
    db.insert("users", user3);
    uint64_t user3ID = db.query("users", user3findTrue)["id"];
    EXPECT_TRUE(db.update("users", user3ID, user3Update));
    json result = db.query("users", user3findTrue);
    EXPECT_EQ(result["password"], user3Update["password"]);
    EXPECT_EQ(result["username"], user3Update["username"]);
  }
}

TEST_F(JsonDataBaseTest, EndToEndCRUDOperations) {
  {
    // ToDO:add EndToEndCRUDOperations
  }
}