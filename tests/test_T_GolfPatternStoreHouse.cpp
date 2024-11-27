
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include "T_GolfPatternStorehouse.h"

using namespace testing;
using namespace std;

TEST(T_GolfPatternStoreHouse, T_GolfPatternStoreHouse)
{
    T_GolfPatternStorehouse sh1;

    EXPECT_EQ(sh1.patterns.size(), 0);
    EXPECT_EQ(sh1.getPattern(0), nullptr);
    EXPECT_EQ(sh1.getPattern(1), nullptr);
    EXPECT_EQ(sh1.getPattern("pattern1"), nullptr);

    EXPECT_NO_THROW(sh1.rmPattern(0));
    EXPECT_NO_THROW(sh1.rmPattern(1));
    EXPECT_NO_THROW(sh1.rmPattern("pattern2"));

    // ASSERT_THAT(0, Eq(0));
}
