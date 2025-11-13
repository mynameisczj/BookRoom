#include "core/database/jsondb.hpp"
#include "core/database/operation_builder.hpp"
#include "core/entities/common.hpp"
#include <cstdio>
#include <fstream>
#include <gtest/gtest.h>

class OperationBuliderTest : public ::testing::Test {
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
TEST_F(OperationBuliderTest, TestCreateTable) {
  {
    EXPECT_FALSE(testFileExists());
    JsonDatabase db(test_db_path);
    OperationBuilder Opbuilder;
    json result = Opbuilder.create("users", user_columns).execute(db);
    EXPECT_TRUE(testFileExists());
    EXPECT_EQ(result["success"], true);
  }
}
TEST_F(OperationBuliderTest, TestQuery) {
  {
    JsonDatabase db(test_db_path);
    OperationBuilder Opbuilder;
    json result = Opbuilder.create("users", user_columns).execute(db);
    Opbuilder.reset();
    uint64_t user1ID = db.insert("users", user1);
    EXPECT_EQ(user1ID, db.query("users", user1findTrue)["id"]);

    // uint64_t user2ID = db.insert("users", user2);
    result = Opbuilder.from("users")
                 .query()
                 .by("username", user1["username"].get<std::string>())
                 .execute(db);
    EXPECT_EQ(result["id"], user1ID);

    Opbuilder.reset();
    result =
        Opbuilder.from("users").query().by("username", "Dolores").by("id", user1ID).execute(db);
    EXPECT_EQ(result["employeeID"], user1["employeeID"]);
  }
}
TEST_F(OperationBuliderTest, TestInsert) {
  {
    JsonDatabase db(test_db_path);
    OperationBuilder Opbuilder;
    json result = Opbuilder.create("users", user_columns).execute(db);
    Opbuilder.reset();
    result = Opbuilder.from("user").insert(user1).execute(db);
    EXPECT_EQ(result["success"], true);

    result = Opbuilder.from("users")
                 .query()
                 .by("username", user1["username"].get<std::string>())
                 .execute(db);
    EXPECT_EQ(result["id"], db.query("users", user1findTrue)["id"]);

    Opbuilder.reset();
    result = Opbuilder.from("user").insert(user1).execute(db);
    EXPECT_EQ(result["success"], false);

    result = Opbuilder.from("users")
                 .query()
                 .by("username", user1["username"].get<std::string>())
                 .execute(db);
    EXPECT_EQ(result["id"], db.query("users", user1findTrue)["id"]);
  }
}
TEST_F(OperationBuliderTest, TestRemove) {
  {
    JsonDatabase db(test_db_path);
    OperationBuilder Opbuilder;
    json result = Opbuilder.create("users", user_columns).execute(db);
    Opbuilder.reset();
    uint64_t user1ID = db.insert("users", user1);
    EXPECT_EQ(user1ID, db.query("users", user1findTrue)["id"]);

    // uint64_t user2ID = db.insert("users", user2);
    result = Opbuilder.from("users").query().by("username", "Dolores").execute(db);
    EXPECT_EQ(result["id"], user1ID);

    Opbuilder.reset();
    result =
        Opbuilder.from("users").query().by("username", "Dolores").by("id", user1ID).execute(db);
    EXPECT_EQ(result["employeeID"], user1["employeeID"]);

    Opbuilder.reset();
    Opbuilder.from("users").remove(user1ID);
    Opbuilder.reset();
    result = Opbuilder.from("users").query().by("username", "Dolores").execute(db);
    EXPECT_TRUE(result.empty());
  }
}
TEST_F(OperationBuliderTest, TestUpate) {
  {
    JsonDatabase db(test_db_path);
    OperationBuilder Opbuilder;
    json result = Opbuilder.create("users", user_columns).execute(db);
    Opbuilder.reset();
    uint64_t user3ID = db.insert("users", user3);
    EXPECT_EQ(user3ID, db.query("users", user3findTrue)["id"]);

    result = Opbuilder.from("users").update(user3Update, user3ID).execute(db);
    EXPECT_EQ(result["success"], true);

    result = db.query("users", user3findTrue);
    EXPECT_EQ(result["password"], user3Update["password"]);
    EXPECT_EQ(result["username"], user3Update["username"]);
  }
}
TEST_F(OperationBuliderTest, EndToEndCRUDOperations) {
  {
    // ToDO:add EndToEndCRUDOperations
  }
}