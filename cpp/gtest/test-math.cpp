#include "gtest/gtest.h"
#include "math.h"

TEST(MathTest, FirstCase)
{
    EXPECT_EQ(2, add(1, 1));
    EXPECT_EQ(8, add(3, 5));
}

TEST(MathTest, SecondCase)
{
    EXPECT_EQ(20, add(10, 10));
    EXPECT_EQ(80, add(3, 5));
}
