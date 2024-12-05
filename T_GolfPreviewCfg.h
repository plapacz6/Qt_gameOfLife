#ifndef T_GOLFPREVIEWCFG_H
#define T_GOLFPREVIEWCFG_H
#include "T_GolfIndex.h"
#include "T_Golf_engine.h"
#include <cstdlib>

/**
 * @brief The T_GolfPreviewCfg class
 * coordinates of fragment GolfBoard, that may be used as preview
 *
 * automatically set miniaml sensible values
 * for example if board is less than required previe, size of previe is shrink to size of board.
 * if starting index are inside board, but requred width or hight cause exceed size of board,
 * width/hight is shrinken to maximal allowed value
 *
 * default (not set) values of T_GolfPreviewCfg are:
 * 0,0  - index of begining point of previevw
 * 0, 0 - size (width, hight) of preview
 *
 * TODO: correct tests, and this class methdods code
 */
class T_GolfPreviewCfg
{
    size_t start_r;
    size_t start_c;
    size_t length_r;
    size_t length_c;
    T_Golf_engine& Golf_engine_;
    void invalidate();
public:
    T_GolfPreviewCfg(T_Golf_engine& Golf_engine_);
    void row(size_t r_);
    void col(size_t c_);
    void height(size_t h_);
    void width(size_t w_);

    void center_row();
    void center_col();

    void size_zero(); //size 0x0, index no change
    void size_ten();  //size 10x10 (or less if board size is not big enought)
    void size_scale(int x);  //multiply of x (or less)
    void size_square(int xy);  //previe of square shape of xy-length edges (or less)

    size_t row();
    size_t col();
    size_t height();
    size_t width();
    T_GolfIndex idx();
    T_GolfIndex length();
    /**
     * @brief size, and indicate if cfg is set
     * @return T_GolfIndex interpretd as number of rows and cols
     * if their are 0, the Cfg is not set yet, so checking size() is indicator
     * if row() and col() have sense
     */
    T_GolfIndex size();
};

#endif // T_GOLFPREVIEWCFG_H
