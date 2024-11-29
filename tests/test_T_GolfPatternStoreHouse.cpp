
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include "T_GolfPatternStorehouse.h"

using namespace testing;
using namespace std;

TEST(T_GolfPatternStoreHouse, empty)
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

TEST(T_GolfPatternStoreHouse, add_pattern_object_1_or_2) {
    T_GolfPatternStorehouse sh1;
    EXPECT_EQ(sh1.patterns.size(), 0);
    EXPECT_EQ(sh1.getPattern(0), nullptr);
    T_GolfPatternDescription pt1("pattern1");
    T_GolfPatternDescription pt2("pattern2");
    T_GolfPatternDescription *ptr_pt1 = &pt1;
    sh1.addPattern(pt1);
    sh1.addPattern(pt2);
    EXPECT_EQ(sh1.patterns.size(), 2);
    EXPECT_NE(sh1.getPattern(0), nullptr);
    EXPECT_NE(sh1.getPattern(0), ptr_pt1);  //patterns are copied
}

TEST(T_GolfPatternStoreHouse, creation_copy_assignment) {
    T_GolfPatternStorehouse sh1;
    T_GolfPatternStorehouse *ptr_sh2 = new T_GolfPatternStorehouse;
    T_GolfPatternDescription pt1("pattern1");
    ptr_sh2->addPattern(pt1);
    T_GolfPatternStorehouse sh3 = *ptr_sh2;
    T_GolfPatternStorehouse *ptr_sh4 = new T_GolfPatternStorehouse;
    *ptr_sh4 = *ptr_sh2;
    T_GolfPatternStorehouse sh5 = T_GolfPatternStorehouse(*ptr_sh2);

    EXPECT_NE(&ptr_sh2->patterns, &sh3.patterns);   //std::vector is deep copied
    EXPECT_NE(&ptr_sh2->patterns, &ptr_sh4->patterns);
    EXPECT_NE(&ptr_sh2->patterns, &sh5.patterns);

    EXPECT_NO_THROW(delete ptr_sh2);

    EXPECT_NO_THROW(sh3.getPattern(0));
    EXPECT_NO_THROW(ptr_sh4->getPattern(0));
    EXPECT_NO_THROW(sh5.getPattern(0));
    EXPECT_NO_THROW(delete ptr_sh4);
}

TEST(T_GolfPatternStoreHouse, rm) {
    T_GolfPatternStorehouse sh1;
    EXPECT_EQ(sh1.patterns.size(), 0);
    EXPECT_EQ(sh1.getPattern(0), nullptr);

    T_GolfPatternDescription pt1("pattern1");
    T_GolfPatternDescription pt2("pattern2");
    T_GolfPatternDescription pt3("pattern3");
    T_GolfPatternDescription pt4("pattern4");

    sh1.addPattern(pt1);
    sh1.addPattern(pt2);
    sh1.addPattern(pt3);
    sh1.addPattern(pt4);
    EXPECT_EQ(sh1.patterns.size(), 4);
    EXPECT_EQ(sh1.getPattern(1)->getName(), "pattern2");

    sh1.rmPattern("pattern2");
    EXPECT_EQ(sh1.patterns.size(), 3);
    EXPECT_EQ(sh1.getPattern("pattern2"), nullptr);
    EXPECT_EQ(sh1.getPattern(1)->getName(), "pattern3");

    sh1.rmPattern(1); // rm "pattern3" now
    EXPECT_EQ(sh1.patterns.size(), 2);
    EXPECT_EQ(sh1.getPattern("pattern3"), nullptr);
    EXPECT_EQ(sh1.getPattern(1)->getName(), "pattern4");
    EXPECT_EQ(sh1.getPattern(2), nullptr);
}

TEST(T_GolfPatternStoreHouse, getPattern) {
    T_GolfPatternStorehouse sh1;
    EXPECT_EQ(sh1.patterns.size(), 0);
    EXPECT_EQ(sh1.getPattern(0), nullptr);

    T_GolfPatternDescription pt1("pattern1");
    T_GolfPatternDescription pt2("pattern2");
    T_GolfPatternDescription pt3("pattern3");
    T_GolfPatternDescription pt4("pattern4");

    sh1.addPattern(pt1);
    sh1.addPattern(pt2);
    sh1.addPattern(pt3);
    sh1.addPattern(pt4);
    EXPECT_EQ(sh1.patterns.size(), 4);
    EXPECT_EQ(sh1.getPattern(1)->getName(), "pattern2");
    EXPECT_EQ(sh1.getPattern("pattern3")->getName(), "pattern3");

    //checking the possibility of changing the obtained pattern
    EXPECT_NO_THROW(sh1.getPattern("pattern3")->setName("pattern3a"));
    EXPECT_EQ(sh1.getPattern("pattern3"), nullptr);
    EXPECT_EQ(sh1.getPattern("pattern3a")->getName(), "pattern3a");
}

TEST(T_GolfPatternStoreHouse, add_pattern_name_and_index) {
    T_GolfPatternStorehouse sh1;
    EXPECT_EQ(sh1.patterns.size(), 0);
    EXPECT_EQ(sh1.getPattern(0), nullptr);

    sh1.addPattern("pattern3", { T_GolfIndex{1,2}, T_GolfIndex{3, 4}});
    EXPECT_EQ(sh1.getPattern("pattern4"), nullptr);
    EXPECT_NE(sh1.getPattern("pattern3"), nullptr);
    EXPECT_EQ(sh1.getPattern("pattern3")->getName(), "pattern3");
    EXPECT_EQ(sh1.getPattern("pattern3")->begin()->col, 1 );
    EXPECT_EQ((sh1.getPattern("pattern3")->begin() + 1)->row, 4 );

}

TEST(T_GolfPatternStoreHouse, add_pattern_name_rows_cols) {
    T_GolfPatternStorehouse sh1;
    EXPECT_EQ(sh1.patterns.size(), 0);
    EXPECT_EQ(sh1.getPattern(0), nullptr);

    sh1.addPattern("pattern4", {5, 6, 7, 8 });
    EXPECT_EQ(sh1.getPattern("pattern3"), nullptr);
    EXPECT_EQ(sh1.getPattern("pattern4")->getName(), "pattern4");
    EXPECT_EQ(sh1.getPattern("pattern4")->begin()->col, 5 );
    EXPECT_EQ((sh1.getPattern("pattern4")->begin() + 1)->row, 8 );
}

