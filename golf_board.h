#ifndef GOLF_BOARD_H
#define GOLF_BOARD_H

#include <QAbstractTableModel>
#include <QObject>
#include <array>
#include <QDebug>
#include "T_Golf_engine.h"

enum {Golf_ROWS = Golf_R, Golf_COLS = Golf_C, Golf_DATASIZE = Golf_ROWS * Golf_COLS};

class T_GolfBoard : public QAbstractTableModel
{
    Q_OBJECT

    bool editable_state;
public:
    QDebug dbg_out;
    // std::array<bool, Golf_DATASIZE> Golf_data;
    //bool Golf_data[Golf_ROWS][Golf_COLS];
    bool (**ptr_Golf_data)[Golf_ROWS];
    QString pattern_name;

    T_GolfBoard(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::BackgroundRole) override; //Qt::EditRole)
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void InitData_chessboard();
    void InitData_PatternName(QString p_name);

public:
signals:
    // void signal_GolfBoardCalculated(std::array<bool, Golf_DATASIZE>& GolfData);
    void signal_GolfBoardCalculated();
    // void signal_GolfBoardSetPattern();

public slots:
    void slot_GolfBoardClear();
    void slot_GolfBoardInitial();
    void slot_GolfBoardSetPattern();
    void slot_GolfCalculate();
    // void slot_GolfBoardStateUpdate(std::array<bool, Golf_DATASIZE>& GolfData);
    void slot_GolfBoardStateUpdate();
    void slot_GolfBoardSetPattern_glider();

};

#endif // GOLF_BOARD_H
