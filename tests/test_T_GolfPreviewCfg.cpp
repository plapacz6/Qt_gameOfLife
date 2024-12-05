
#include <gmock/gmock-matchers.h>
#include <gtest/gtest.h>
#include "T_GolfPreviewCfg.h"

using namespace testing;

T_Golf_engine Golf_engine_global_;
size_t width;
size_t height;
size_t golf_width;
size_t golf_height;

TEST(T_GolfPreviewCfg, col_width)
{
    golf_width = Golf_engine_global_.get_cols();

    T_GolfPreviewCfg  gcfg(Golf_engine_global_);
    EXPECT_EQ(gcfg.col(), 0);
    EXPECT_EQ(gcfg.width(), 0);

    gcfg.width(0);
    EXPECT_EQ(gcfg.width(), 0);
    gcfg.col(0);
    EXPECT_EQ(gcfg.col(), 0);

    gcfg.width(golf_width - 2);
    EXPECT_EQ(gcfg.width(), golf_width - 2);
    gcfg.col(10);
    EXPECT_EQ(gcfg.col(), 10);
    EXPECT_EQ(gcfg.width(), golf_width - 10);

    gcfg.col(golf_width);
    EXPECT_EQ(gcfg.col(), golf_width - 1);
    EXPECT_EQ(gcfg.width(), 1);

    gcfg.col( -golf_width);
    EXPECT_EQ(gcfg.col(), golf_width - 1);
    EXPECT_EQ(gcfg.width(), 1);
    gcfg.width( -golf_width);
    EXPECT_EQ(gcfg.col(), golf_width - 1);
    EXPECT_EQ(gcfg.width(), 1);
}

TEST(T_GolfPreviewCfg, row_height)
{
    golf_height = Golf_engine_global_.get_rows();

    T_GolfPreviewCfg  gcfg(Golf_engine_global_);
    EXPECT_EQ(gcfg.row(), 0);
    EXPECT_EQ(gcfg.height(), 0);

    gcfg.height(0);
    EXPECT_EQ(gcfg.height(), 0);
    gcfg.row(0);
    EXPECT_EQ(gcfg.row(), 0);

    gcfg.height(golf_height - 2);
    EXPECT_EQ(gcfg.height(), golf_height - 2);
    gcfg.row(10);
    EXPECT_EQ(gcfg.row(), 10);
    EXPECT_EQ(gcfg.height(), golf_height - 10);

    gcfg.row(golf_height);
    EXPECT_EQ(gcfg.row(), golf_height - 1);
    EXPECT_EQ(gcfg.height(), 1);

    gcfg.row( -golf_height);
    EXPECT_EQ(gcfg.row(), golf_height - 1);
    EXPECT_EQ(gcfg.height(), 1);
    gcfg.height( -golf_height);
    EXPECT_EQ(gcfg.row(), golf_height - 1);
    EXPECT_EQ(gcfg.height(), 1);
}

TEST(T_GolfPreviewCfg, idx_size_length_0)
{
    golf_width = Golf_engine_global_.get_cols();
    golf_height = Golf_engine_global_.get_rows();

    T_GolfPreviewCfg  gcfg(Golf_engine_global_);

    T_GolfIndex idx;
    T_GolfIndex size;
    T_GolfIndex length;
    \
    gcfg.row(golf_height - 1);
    gcfg.col(golf_width - 1);
    gcfg.height(golf_height);
    gcfg.width(golf_width);

    idx = gcfg.idx();
    size = gcfg.size();
    length = gcfg.length();

    EXPECT_EQ(idx.col, gcfg.col());
    EXPECT_EQ(idx.row, gcfg.row());
    EXPECT_EQ(size.col, gcfg.width());
    EXPECT_EQ(size.row, gcfg.height());
    EXPECT_EQ(length.col, gcfg.width());
    EXPECT_EQ(length.row, gcfg.height());
}

TEST(T_GolfPreviewCfg, center)
{
    golf_width = Golf_engine_global_.get_cols();
    golf_height = Golf_engine_global_.get_rows();

    T_GolfPreviewCfg  gcfg(Golf_engine_global_);
    gcfg.width(golf_width);
    gcfg.height(golf_height);
    gcfg.center_row();
    gcfg.center_col();
    EXPECT_EQ(gcfg.col(), 0);
    EXPECT_EQ(gcfg.row(), 0);
    size_t shift_col_times_2 = 11;
    size_t shift_row_times_2 = 19;
    if(golf_width >= shift_col_times_2 && golf_height >= shift_row_times_2)
    gcfg.width(golf_width - shift_col_times_2);
    gcfg.height(golf_height - shift_row_times_2);
    gcfg.center_row();
    gcfg.center_col();
    EXPECT_EQ(gcfg.col(), shift_col_times_2 / 2);
    EXPECT_EQ(gcfg.row(), shift_row_times_2 / 2);
}
