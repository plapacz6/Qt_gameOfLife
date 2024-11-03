#include "golf_board.h"
#include <QtDebug>
#include <QBrush>
#include <QTime>
#include "T_Golf_engine.h"

extern T_Golf_engine Golf_engine;

T_GolfBoard::T_GolfBoard(QObject *parent)
    :
    QAbstractTableModel(parent),
    dbg_out(QtDebugMsg)
{
    ptr_Golf_data = &(Golf_engine.data_new);
    Golf_engine.Torus = true;
    pattern_name = QString("blinker");

    editable_state = true;
    // InitData_chessboard();
    InitData_PatternName(pattern_name);
}

int T_GolfBoard::rowCount(const QModelIndex &parent) const
{
    return Golf_ROWS;
}
int T_GolfBoard::columnCount(const QModelIndex &parent) const
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

        if((*ptr_Golf_data)[row][col]) {
            return QString("T");
        }
        else {
            return QString("F");
        }
    }
    if(role == Qt::BackgroundRole)
    {
        if((*ptr_Golf_data)[row][col]) {
            return QBrush(Qt::red);
        }
        else {
            return QBrush(Qt::gray);
        }
    }
    return QVariant();
}

bool T_GolfBoard::setData(const QModelIndex &index, const QVariant &value, int role)
{
    // qDebug() << "T_GolfBoard::setData() : role:" << role;
    if(role == Qt::BackgroundRole) {
        (*ptr_Golf_data)[index.row()][index.column()] =
            (value == QBrush(Qt::red)) ? true : false;
    }
    if(role == Qt::DisplayRole) {
        (*ptr_Golf_data)[index.row()][index.column()] =
            (value == QString("T")) ? true : false;
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

void T_GolfBoard::InitData_chessboard()
{
    qDebug() << "InitData_chessboard() - member call";
    QDebug out(QtDebugMsg);
    out.nospace();

    size_t row_data = 0;
    size_t col_data = 0;
    for(; row_data < Golf_ROWS; ++row_data) {
        col_data = 0;
        for(; col_data < Golf_COLS; ++col_data) {
            // out << "[" << (row_data % 2) << "," << ((col_data + 1) % 2) << "]";
            if((row_data % 2) ? (col_data % 2) : ((col_data + 1) % 2)){
                (*ptr_Golf_data)[row_data][col_data] = true;
            }
            else {
                (*ptr_Golf_data)[row_data][col_data] = false;
            }
        }
        // out << "\n";
    }
}

void T_GolfBoard::InitData_PatternName(QString p_name)
{
    qDebug() << "InitData_PatternName(" << p_name << ")";
    Golf_engine.reset();
    size_t r = 1;
    size_t c = 1;
    if(p_name == QString("blinker")) {
        if(Golf_R >= 5 && Golf_C >= 5) {
            (*ptr_Golf_data)[r + 1][c + 0] = true;
            (*ptr_Golf_data)[r + 1][c + 1] = true;
            (*ptr_Golf_data)[r + 1][c + 2] = true;
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
            if((*ptr_Golf_data)[row][col] == true){
                out << "#";
                setData(index(row, col), QBrush(Qt::red), Qt::BackgroundRole);
                setData(index(row, col), QString("T"), Qt::DisplayRole);
            }
            else {
                out << "_";
                setData(index(row, col), QBrush(Qt::gray), Qt::BackgroundRole);
                setData(index(row, col), QString("F"), Qt::DisplayRole);
            }            
        }
        out << "\n";
    }

    emit dataChanged( index(0,0), index(Golf_ROWS - 1, Golf_COLS - 1) );
}
/* to infrom view about data changing model send signal that indicates what
 * range of cells has changed
 */
