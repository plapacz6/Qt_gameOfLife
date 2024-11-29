#ifndef T_TOPLEFTBOTTOMRIGHT_RECTTABLEAREA_H
#define T_TOPLEFTBOTTOMRIGHT_RECTTABLEAREA_H
#include <QModelIndex>
class T_TopLeftBottomRight_RectTableArea
{
public:
    T_TopLeftBottomRight_RectTableArea();
    QModelIndex top_left;
    QModelIndex bottom_right;
    QModelIndex& tl = top_left;
    QModelIndex& br = bottom_right;
};

#endif // T_TOPLEFTBOTTOMRIGHT_RECTTABLEAREA_H
