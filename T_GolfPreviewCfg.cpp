#include "T_GolfPreviewCfg.h"


void T_GolfPreviewCfg::invalidate()
{
    start_r = start_c = length_r = length_c = 0;
}

T_GolfPreviewCfg::T_GolfPreviewCfg(T_Golf_engine &Golf_engine_)
    : Golf_engine_{Golf_engine_}
{
    invalidate();
}

void T_GolfPreviewCfg::row(size_t r_)
{
    size_t golf_rows = Golf_engine_.get_rows();
    if(r_ < golf_rows){
        start_r = r_;
    }
    else {
        start_r = golf_rows - 1;
    }
    if(start_r + length_r > golf_rows) {
        length_r = golf_rows - start_r;
    }
}

void T_GolfPreviewCfg::col(size_t c_)
{
    size_t golf_cols = Golf_engine_.get_cols();
    if(c_ < golf_cols){
        start_c = c_;
    }
    else {
        start_c = golf_cols - 1;
    }
    if(start_c + length_c > golf_cols) {
        length_c = golf_cols - start_c;
    }
}

void T_GolfPreviewCfg::height(size_t h_)
{
    size_t golf_rows = Golf_engine_.get_rows();
    if(start_r + h_ < golf_rows) {
        length_r = h_;
    }
    else {
        length_r = golf_rows - start_r;
    }
}

void T_GolfPreviewCfg::width(size_t w_)
{
    size_t golf_cols = Golf_engine_.get_cols();
    if(start_c + w_ < golf_cols) {
        length_c = w_;
    }
    else {
        length_c = golf_cols - start_c;
    }
}

void T_GolfPreviewCfg::center_row()
{
    size_t golf_rows = Golf_engine_.get_rows();
    start_r = (golf_rows >= length_r)
        ? (golf_rows - length_r) / 2
        :   0
    ;
}

void T_GolfPreviewCfg::center_col()
{
    size_t golf_cols = Golf_engine_.get_cols();
    start_c = (golf_cols >= length_c)
                  ? (golf_cols - length_c) / 2
                  :   0
        ;
}

void T_GolfPreviewCfg::size_zero()
{
    length_c = length_r = 0;
}

void T_GolfPreviewCfg::size_ten()
{
    width(10);
    height(10);
}

void T_GolfPreviewCfg::size_scale(int x)
{
    width(width() * x);
    height(height() * x);
}

void T_GolfPreviewCfg::size_square(int xy)
{
    width(xy);
    height(xy);
}



size_t T_GolfPreviewCfg::row()
{
    return start_r;
}

size_t T_GolfPreviewCfg::col()
{
    return start_c;
}

size_t T_GolfPreviewCfg::height()
{
    return length_r;
}

size_t T_GolfPreviewCfg::width()
{
    return length_c;
}



T_GolfIndex T_GolfPreviewCfg::idx()
{
    return T_GolfIndex{start_c, start_r};
}

T_GolfIndex T_GolfPreviewCfg::length()
{
    return T_GolfIndex{length_c, length_r};
}

T_GolfIndex T_GolfPreviewCfg::size()
{
    return T_GolfIndex{length_c, length_r};
}
