#include "TQ_GolfBoardPreview.h"
#include <QtDebug>
#include <QBrush>
#include <QTime>
#include "T_Golf_engine.h"
#include <cassert>
#include <vector>
#include <QList>

using namespace std;

extern T_Golf_engine Golf_engine_global;

T_GolfBoardPreview::T_GolfBoardPreview(QObject *parent)
    :
    QAbstractTableModel(parent),
    Golf_engine(Golf_engine_global),
    dbg_out(QtDebugMsg)
{
    // ptr_Golf_data = &(Golf_engine.data_new);     api changed
    starting_row_of_view = 0;
    starting_col_of_view = 0;

    slot_GolfBoardSetPreviewStartRow(
        (Golf_R > Golf_ROWS)
            ? (Golf_R - Golf_ROWS) / 2
            :   0
        );
    slot_GolfBoardSetPreviewStartCol(
        (Golf_C > Golf_COLS)
            ? (Golf_C - Golf_COLS) / 2
            :   0
        );

    pattern_name = QString("initial");

    editable_state = false;

    InitData_PatternName(pattern_name);
}

int T_GolfBoardPreview::rowCount(const QModelIndex & /*parent*/) const
{
    return Golf_ROWS;
}
int T_GolfBoardPreview::columnCount(const QModelIndex & /*parent*/) const
{
    return Golf_COLS;
}
QVariant T_GolfBoardPreview::data(const QModelIndex &index, int role) const
{
    int row = starting_row_of_view + index.row();
    int col = starting_col_of_view + index.column();

    // qDebug() << __PRETTY_FUNCTION__  << QString("row %1, col %2, role %3").arg(row).arg(col).arg(role);

    if(role == Qt::UserRole)
    {
        if(Golf_engine.get_cell(row, col)) {
            return QVariant(true);
        }
        else {
            return QVariant(false);
        }
    }
    // if(role == Qt::DisplayRole)
    // {
    //     if(Golf_engine.get_cell(row, col)) {
    //         return QString("_");
    //     }
    //     else {
    //         return QString(" ");
    //     }
    // }
    if(role == Qt::BackgroundRole)
    {
        if(Golf_engine.get_cell(row, col)) {
            return cell_color_full;
        }
        else {
            return cell_color_empty;
        }
    }
    return QVariant();
}


bool T_GolfBoardPreview::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // qDebug() << __PRETTY_FUNCTION__ << "role:" << role;
    int row = starting_row_of_view + index.row();
    int col = starting_col_of_view + index.column();
    if(
        role == Qt::UserRole
    ) {
        Golf_engine.set_cell(row, col, value.toBool());
        return true;
    }
    return false;
}

Qt::ItemFlags T_GolfBoardPreview::flags(const QModelIndex &index) const
{
    if(editable_state) {
        return Qt::ItemIsSelectable | Qt::ItemIsEnabled;
    }
    else {
        return Qt::NoItemFlags;
    }
}

// ----------------------- helper methods ----------------------------------
void T_GolfBoardPreview::InitData_chessboard()
{
    qDebug() << __PRETTY_FUNCTION__;
    QDebug out(QtDebugMsg);
    out.nospace();

    for(size_t row_data = starting_row_of_view;
         row_data < Golf_ROWS + starting_row_of_view; ++row_data) {
        for(size_t col_data = starting_col_of_view;
             col_data < Golf_COLS + starting_col_of_view; ++col_data) {
            out << "[" << (row_data % 2) << "," << ((col_data + 1) % 2) << "]";
            if((row_data % 2) ? (col_data % 2) : ((col_data + 1) % 2)){
                Golf_engine.set_cell(row_data, col_data, true);
            }
            else {
                Golf_engine.set_cell(row_data, col_data, false);
            }
        }
        out << "\n";
    }
}

void T_GolfBoardPreview::InitData_PatternName(QString p_name)
{
    qDebug() << "InitData_PatternName(" << p_name << ")";
    Golf_engine.reset();    
    size_t r = starting_row_of_view + 1;
    size_t c = starting_col_of_view + 1;
    bool pattern_seted = false;
    if(p_name == QString("initial")) {
        InitData_chessboard();
        pattern_seted = true;
    }
    if(p_name == QString("blinker")) {
        if(Golf_R >= 5 && Golf_C >= 5) {
            Golf_engine.set_cell(r + 1, c + 0,  true);
            Golf_engine.set_cell(r + 1, c + 1,  true);
            Golf_engine.set_cell(r + 1, c + 2,  true);
            pattern_seted = true;
        }        
        else {
            qDebug() << "board to small for pattern: " << p_name;
            return;
        }
    }
    if(p_name == QString("glider")) {
        if(Golf_R >= 5 && Golf_C >= 5) {
            Golf_engine.set_cell(r + 0, c + 1,  true);
            Golf_engine.set_cell(r + 1, c + 2,  true);
            Golf_engine.set_cell(r + 2, c + 0,  true);
            Golf_engine.set_cell(r + 2, c + 1,  true);
            Golf_engine.set_cell(r + 2, c + 2,  true);
            pattern_seted = true;
        }
        else {
            qDebug() << "board to small for pattern: " << p_name;
            return;
        }
    }

    if(pattern_seted) {
        this->getMinRectContainingPattern();
    }
    else {
        qDebug() << "unknown pattern name" << p_name;
    }

}

T_TopLeftBottomRight_RectTableArea T_GolfBoardPreview::getMinRectContainingPattern()
{
    qDebug() << __PRETTY_FUNCTION__;
    // vector<size_t> examined_row;
    // vector<size_t> examined_col;

    // QList<int> examined_row1;
    // QList<int> examined_col1;
    // QList<int> examined_row2;
    // QList<int> examined_col2;
    int r1, r2, c1, c2;
    r1 = -1;
    for(int ri = 0; ri < board_preview_hight; ++ri){
        for(int ci = 0; ci < board_preview_width; ++ci) {
            // if(data(index(ri, ci)).toBool()) {
            if(Golf_engine.get_cell(ri + starting_row_of_view, ci + starting_col_of_view)){
                r1 = ri;
                break;
            }
        }
        if(r1 != -1) {
            break;
        }
    }

    r2 = -1;
    for(int ri = board_preview_hight -1; ri >= 0; --ri){
        for(int ci = 0; ci < board_preview_width; ++ci) {
            // if(data(index(ri, ci)).toBool()) {
            if(Golf_engine.get_cell(ri + starting_row_of_view, ci + starting_col_of_view)){
                r2 = ri;
                break;
            }
        }
        if(r2 != -1) {
            break;
        }
    }

    c1 = -1;
    for(int ci = 0; ci < board_preview_width; ++ci) {
        for(int ri = 0; ri < board_preview_hight; ++ri){
            // if(data(index(ri, ci)).toBool()) {
            if(Golf_engine.get_cell(ri + starting_row_of_view, ci + starting_col_of_view)){
                c1 = ci;
                break;
            }
        }
        if(c1 != -1) {
            break;
        }
    }

    c2 = -1;
    for(int ci = board_preview_width - 1; ci >= 0; --ci) {
        for(int ri = 0; ri < board_preview_hight; ++ri){
            // if(data(index(ri, ci)).toBool()) {
            if(Golf_engine.get_cell(ri + starting_row_of_view, ci + starting_col_of_view)){
                c2 = ci;
                break;
            }
        }
        if(c2 != -1) {
            break;
        }
    }

    T_TopLeftBottomRight_RectTableArea tlbr;
    tlbr.bottom_right = index(r2, c2);
    tlbr.top_left = index(r1, c1);
    qDebug() << "pattern area: r1:" << r1 << " c1:" << c1 << " r2:" << r2 << " c2:" << c2;
    return tlbr;
}

// ----------------------- slots  ----------------------------------

void T_GolfBoardPreview::slot_GolfBoardClear()
{
    qDebug() << "slot_GolfBoardClear()";
    Golf_engine.reset();
    emit this->signal_GolfBoardCalculated(); //Golf_data);
}

void T_GolfBoardPreview::slot_GolfBoardInitial()
{
    qDebug() << "slot_GolfBoardInitial()";
    this->InitData_chessboard();
    emit this->signal_GolfBoardCalculated();
}

void T_GolfBoardPreview::slot_GolfBoardSetPattern()
{
    qDebug() << "slot_GolfBoardSetPattern(" << this->pattern_name << ")";
    InitData_PatternName(this->pattern_name);
    emit this->signal_GolfBoardCalculated();
}

void T_GolfBoardPreview::slot_GolfBoardSetPatternNearPreviewCenter(QString &)
{
    qDebug() << "slot_GolfBoardSetPatternNearPreviewCenter(QString) : not implemented";
}

void T_GolfBoardPreview::slot_GolfCalculate()
{
    qDebug() << __PRETTY_FUNCTION__;
    Golf_engine.calculate();
    emit this->signal_GolfBoardCalculated();
}

void T_GolfBoardPreview::slot_GolfBoardStateUpdate()
{
    qDebug() << __PRETTY_FUNCTION__;

    emit dataChanged( index(0,0), index(Golf_ROWS - 1, Golf_COLS - 1) );
}

void T_GolfBoardPreview::slot_GolfBoardSetPattern_blinker()
{
    pattern_name = QString("blinker");
    InitData_PatternName(this->pattern_name);
    emit this->signal_GolfBoardCalculated();
}

void T_GolfBoardPreview::slot_GolfBoardSetPattern_glider()
{
    pattern_name = QString("glider");
    InitData_PatternName(this->pattern_name);
    emit this->signal_GolfBoardCalculated();
}

void T_GolfBoardPreview::slot_GolfBoardSwitchEditor()
{
    qDebug() << __PRETTY_FUNCTION__;
    editable_state = editable_state ? false : true;
}

void T_GolfBoardPreview::slot_GolfBoardSetPreviewStartRow(int y)
{
    qDebug() << __PRETTY_FUNCTION__ << "(int: " << y << ")";
    assert(y >= 0);
    assert(y + (board_preview_hight - 1) < Golf_engine.get_rows());  //index + size -> first index after last allowed

    if(board_preview_hight + y < Golf_engine.get_rows()) {
        starting_col_of_view = y;
    }
    else {
        starting_col_of_view = 0;
    }
}

void T_GolfBoardPreview::slot_GolfBoardSetPreviewStartCol(int x)
{
    qDebug() << __PRETTY_FUNCTION__ << "(int: " << x << ")";
    assert(x >= 0);
    assert(x + (board_preview_width - 1) < Golf_engine.get_cols());

    if(board_preview_width + x < Golf_engine.get_cols()) {
        starting_row_of_view = x;
    }
    else {
        starting_row_of_view = 0;
    }
}

/* to infrom view about data changing model send signal that indicates what
 * range of cells has changed
 */
