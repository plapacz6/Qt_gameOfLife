
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include "T_GolfIndex.h"
using namespace testing;

TEST(T_GolfIndex, T_GolfIndex)
{
    T_GolfIndex idx0;
    EXPECT_EQ(idx0.col, 0);
    EXPECT_EQ(idx0.row, 0);
    idx0.col = 1;
    idx0.row = 2;
    EXPECT_EQ(idx0.col, 1);
    EXPECT_EQ(idx0.row, 2);
    T_GolfIndex idx1{3, 4};
    EXPECT_EQ(idx1.col, 3);
    EXPECT_EQ(idx1.row, 4);
    idx1.col = 5;
    idx1.row = 6;
    EXPECT_EQ(idx1.col, 5);
    EXPECT_EQ(idx1.row, 6);
    // ASSERT_THAT(0, Eq(0));
}
