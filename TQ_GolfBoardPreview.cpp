#include "TQ_GolfBoardPreview.h"
#include <QtDebug>
#include <QBrush>
#include <QTime>
#include "T_Golf_engine.h"
#include <cassert>

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

    // qDebug() << "gOfL_board::data()" << QString("row %1, col %2, role %3").arg(row).arg(col).arg(role);

    if(role == Qt::DisplayRole)
    {
        if(Golf_engine.get_cell(row, col)) {
            return QString("_");
        }
        else {
            return QString(" ");
        }
    }
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
    // qDebug() << "T_GolfBoard::setData() : role:    WHY THIS IS" << role;
    int row = starting_row_of_view + index.row();
    int col = starting_col_of_view + index.column();
    if(role == Qt::EditRole || role == Qt::CheckStateRole) {
        Golf_engine.set_cell(row, col, value.toBool()); //(Golf_engine.get_cell(row, col) ? false : true));
    }
}

Qt::ItemFlags T_GolfBoardPreview::flags(const QModelIndex &index) const
{
    if(editable_state) {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    else {
        return Qt::NoItemFlags;
    }
}

// ----------------------- helper methods ----------------------------------
void T_GolfBoardPreview::InitData_chessboard()
{
    qDebug() << "InitData_chessboard() - member call";
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
    if(p_name == QString("initial")) {
        InitData_chessboard();
        return;
    }
    if(p_name == QString("blinker")) {
        if(Golf_R >= 5 && Golf_C >= 5) {
            Golf_engine.set_cell(r + 1, c + 0,  true);
            Golf_engine.set_cell(r + 1, c + 1,  true);
            Golf_engine.set_cell(r + 1, c + 2,  true);
            return;
        }        
        else {
            qDebug() << "board to small for pattern: " << p_name;
        }
    }
    if(p_name == QString("glider")) {
        if(Golf_R >= 5 && Golf_C >= 5) {
            Golf_engine.set_cell(r + 0, c + 1,  true);
            Golf_engine.set_cell(r + 1, c + 2,  true);
            Golf_engine.set_cell(r + 2, c + 0,  true);
            Golf_engine.set_cell(r + 2, c + 1,  true);
            Golf_engine.set_cell(r + 2, c + 2,  true);
            return;
        }
        else {
            qDebug() << "board to small for pattern: " << p_name;
        }
    }
    qDebug() << "unknown pattern name" << p_name;
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
    //Golf_engine.swap_data();
    //this->InitData_chessboard();
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
    qDebug() << "slot_GolfCalculate() : invoked";
    Golf_engine.calculate();
    emit this->signal_GolfBoardCalculated();
}

void T_GolfBoardPreview::slot_GolfBoardStateUpdate()
{
    QDebug out(QtDebugMsg);
    // qDebug() << "slot_GolfBoardStateUpdate() - called";
    out.nospace();
    out << "slot_GolfBoardStateUpdate():\n";

    for(size_t row = 0; row < Golf_ROWS; ++row) {
        for(size_t col = 0; col < Golf_COLS; ++col) {
            if(Golf_engine.get_cell(row, col) == true){
                // out << "#";
                setData(index(row, col), QBrush(Qt::red), Qt::BackgroundRole);
                setData(index(row, col), QString("T"), Qt::DisplayRole);
            }
            else {
                // out << "_";
                setData(index(row, col), QBrush(Qt::gray), Qt::BackgroundRole);
                setData(index(row, col), QString("F"), Qt::DisplayRole);
            }            
        }
        // out << "\n";
    }

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
    editable_state = editable_state ? false : true;
}

void T_GolfBoardPreview::slot_GolfBoardSetPreviewStartRow(int y)
{
    qDebug() << "slot_GolfBoardSetPreviewStartRow(int: " << y << ")";
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
    qDebug() << "slot_GolfBoardSetPreviewStartCol(int: " << x << ")";
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
