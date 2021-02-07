#include "gtest/gtest.h"

int add(int a, int b) { return a + b; }

TEST(AddTest, SholdAddTwoNum) {
  EXPECT_EQ(3, add(1, 2));
  EXPECT_EQ(10000, add(0, 1));
}
