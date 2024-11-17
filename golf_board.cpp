#include "golf_board.h"
#include <QtDebug>
#include <QBrush>
#include <QTime>
#include "T_Golf_engine.h"
#include <cassert>

extern T_Golf_engine Golf_engine_global;

T_GolfBoard::T_GolfBoard(QObject *parent)
    :
    QAbstractTableModel(parent),
    Golf_engine(Golf_engine_global),
    dbg_out(QtDebugMsg)
{
    // ptr_Golf_data = &(Golf_engine.data_new);     api changed
    starting_row_of_view = 0;
    starting_col_of_view = 0;

    pattern_name = QString("initial");

    editable_state = true;

    InitData_PatternName(pattern_name);
}

int T_GolfBoard::rowCount(const QModelIndex & /*parent*/) const
{
    return Golf_ROWS;
}
int T_GolfBoard::columnCount(const QModelIndex & /*parent*/) const
{
    return Golf_COLS;
}
QVariant T_GolfBoard::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();

    // qDebug() << "gOfL_board::data()" << QString("row %1, col %2, role %3").arg(row).arg(col).arg(role);

    if(role == Qt::DisplayRole)
    {
        // if(row == 0 && col == 0)
        // {
        //     return QTime::currentTime().toString();
        // }
        // return QString("%1%2").arg(index.row() + 1).arg(index.column() + 1);

        if(Golf_engine.get_cell(starting_row_of_view + row, starting_row_of_view + col)) {
            return QString("_");
        }
        else {
            return QString(" ");
        }
    }
    if(role == Qt::BackgroundRole)
    {
        if(Golf_engine.get_cell(starting_row_of_view + row, starting_row_of_view + col)) {
            return cell_color_full;
        }
        else {
            return cell_color_empty;
        }
    }
    return QVariant();
}



void T_GolfBoard::InitData_chessboard()
{
    qDebug() << "InitData_chessboard() - member call";
    QDebug out(QtDebugMsg);
    out.nospace();

    size_t row_data = starting_row_of_view;
    size_t col_data = starting_col_of_view;
    for(; row_data < Golf_ROWS + starting_row_of_view; ++row_data) {
        col_data = starting_col_of_view;
        for(; col_data < Golf_COLS + starting_col_of_view; ++col_data) {
            // out << "[" << (row_data % 2) << "," << ((col_data + 1) % 2) << "]";
            if((row_data % 2) ? (col_data % 2) : ((col_data + 1) % 2)){
                Golf_engine.set_cell(row_data, col_data, true);
            }
            else {
                Golf_engine.set_cell(row_data, col_data, false);
            }
        }
        // out << "\n";
    }
}

void T_GolfBoard::InitData_PatternName(QString p_name)
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
            Golf_engine.set_cell(r - 1, c + 1,  true);
            Golf_engine.set_cell(r + 0, c + 2,  true);
            Golf_engine.set_cell(r + 1, c + 0,  true);
            Golf_engine.set_cell(r + 1, c + 1,  true);
            Golf_engine.set_cell(r + 1, c + 2,  true);
            return;
        }
        else {
            qDebug() << "board to small for pattern: " << p_name;
        }
    }
    qDebug() << "unknown pattern name" << p_name;
}

void T_GolfBoard::slot_GolfBoardClear()
{
    qDebug() << "slot_GolfBoardClear()";
    Golf_engine.reset();
    emit this->signal_GolfBoardCalculated(); //Golf_data);
}

void T_GolfBoard::slot_GolfBoardInitial()
{
    qDebug() << "slot_GolfBoardInitial()";
    this->InitData_chessboard();
    //Golf_engine.swap_data();
    //this->InitData_chessboard();
    emit this->signal_GolfBoardCalculated();
}

void T_GolfBoard::slot_GolfBoardSetPattern()
{
    qDebug() << "slot_GolfBoardSetPattern(" << this->pattern_name << ")";
    InitData_PatternName(this->pattern_name);
    emit this->signal_GolfBoardCalculated();
}

void T_GolfBoard::slot_GolfBoardSetPatternNearPreviewCenter(QString &)
{
    qDebug() << "slot_GolfBoardSetPatternNearPreviewCenter(QString) : not implemented";
}

void T_GolfBoard::slot_GolfCalculate()
{
    qDebug() << "slot_GolfCalculate() : invoked";
    Golf_engine.calculate();
    emit this->signal_GolfBoardCalculated();
}

void T_GolfBoard::slot_GolfBoardStateUpdate()
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

void T_GolfBoard::slot_GolfBoardSetPattern_blinker()
{
    pattern_name = QString("blinker");
    InitData_PatternName(this->pattern_name);
    emit this->signal_GolfBoardCalculated();
}

void T_GolfBoard::slot_GolfBoardSetPattern_glider()
{
    pattern_name = QString("glider");
    InitData_PatternName(this->pattern_name);
    emit this->signal_GolfBoardCalculated();
}

void T_GolfBoard::slot_GolfBoardSwitchEditor()
{
    editable_state = editable_state ? false : true;
}

void T_GolfBoard::slot_GolfBoardSetPreviewStartRow(int y)
{
    qDebug() << "slot_GolfBoardSetPreviewStartRow(int)";
    // assert(board_preview_hight + y < Golf_engine.get_rows());
    if(board_preview_hight + y < Golf_engine.get_rows()) {
        starting_col_of_view = board_preview_hight + y;
    }
    else {
        starting_col_of_view = Golf_engine.get_rows() - board_preview_hight;
    }
}

void T_GolfBoard::slot_GolfBoardSetPreviewStartCol(int x)
{
    qDebug() << "slot_GolfBoardSetPreviewStartCol(int)";
    // assert(board_preview_width + x < Golf_engine.get_cols());
    if(board_preview_width + x < Golf_engine.get_cols()) {
        starting_row_of_view = board_preview_width + x;
    }
    else {
        starting_row_of_view = Golf_engine.get_cols() - board_preview_width;
    }
}

/* to infrom view about data changing model send signal that indicates what
 * range of cells has changed
 */

bool T_GolfBoard::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // qDebug() << "T_GolfBoard::setData() : role:" << role;
    if(role == Qt::EditRole || role == Qt::CheckStateRole) {
        Golf_engine.set_cell(
            starting_row_of_view + index.row(),
            starting_col_of_view + index.column(),
            (Golf_engine.get_cell(
                  starting_row_of_view + index.row(),
                  starting_col_of_view + index.column()
                 ) ? false : true
             )
        );
    }
}

Qt::ItemFlags T_GolfBoard::flags(const QModelIndex &index) const
{
    if(editable_state) {
        return Qt::ItemIsEnabled | Qt::ItemIsSelectable;
    }
    else {
        return Qt::NoItemFlags;
    }
}
