#include <gtest/gtest.h>

// 1. 基本测试
TEST(SimpleTest, Addition) {
    EXPECT_EQ(2 + 2, 4);
    EXPECT_NE(5 + 3, 7);
}