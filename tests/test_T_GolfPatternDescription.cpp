
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include "T_GolfPatternDescription.h"
using namespace testing;
using namespace std;
TEST(GolfPatternDescription, constructor_getters_setters)
{
    T_GolfPatternDescription p1("pattern1");

    EXPECT_EQ(string("pattern1"), p1.getName());
    EXPECT_EQ(0, p1.getWidth());
    EXPECT_EQ(0, p1.getHight());
    EXPECT_EQ(p1.size(), 0);

    p1.addPoint(9, 19);
    p1.addPoint(6, 11);
    p1.addPoint(9, 12);
    EXPECT_EQ(p1.begin()->col, 6);
    EXPECT_EQ(p1[0].col, 6);
    EXPECT_EQ(p1[1].col, 9);
    EXPECT_EQ(p1[2].col, 9);
    EXPECT_EQ(p1[0].row, 11);
    EXPECT_EQ(p1[1].row, 12);
    EXPECT_EQ(p1[2].row, 19);
    EXPECT_EQ(((--p1.end()))->row, 19);
    EXPECT_EQ(p1.size(), 3);
    EXPECT_EQ(p1.getWidth(), 3);
    EXPECT_EQ(p1.getHight(), 8);
    size_t i = 0;
    for(auto& p : p1) {
        EXPECT_NE(p.col, 0);
        ++i;
    }
    EXPECT_EQ(i, 3);
    p1.setName("pattern2");
    EXPECT_EQ(string("pattern2"), p1.getName());

    // ASSERT_THAT(0, Eq(0));
}
