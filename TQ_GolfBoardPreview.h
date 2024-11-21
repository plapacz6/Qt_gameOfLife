#ifndef GOLF_BOARD_H
#define GOLF_BOARD_H

#include <QAbstractTableModel>
#include <QObject>
#include <array>
#include <QDebug>
#include <QString>
#include <QBrush>
#include "T_Golf_engine.h"

enum : size_t {
    Golf_ROWS_ = 50,
    Golf_COLS_ = Golf_ROWS_,
    Golf_ROWS = (Golf_R < Golf_ROWS_ ? Golf_R : Golf_ROWS_),
    Golf_COLS = (Golf_C < Golf_COLS_ ? Golf_C : Golf_COLS_),
    Golf_DATASIZE = Golf_ROWS * Golf_COLS
};

class T_GolfBoardPreview : public QAbstractTableModel
{
    Q_OBJECT

    bool editable_state;
    int board_preview_hight = static_cast<int>(Golf_ROWS);
    int board_preview_width = static_cast<int>(Golf_COLS);
    T_Golf_engine& Golf_engine;
    QBrush cell_color_empty = QBrush(Qt::gray);
    QBrush cell_color_full = QBrush(Qt::darkBlue);
public:
    QDebug dbg_out;
    // std::array<bool, Golf_DATASIZE> Golf_data;
    //bool Golf_data[Golf_ROWS][Golf_COLS];
    // bool (**ptr_Golf_data)[Golf_ROWS];   //T_Golf_engine  api changed
    QString pattern_name;
    int starting_row_of_view;   //index : Golf_enigne coordinates from which the board preview starts
    int starting_col_of_view;

    T_GolfBoardPreview(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


    bool setData(const QModelIndex &index, const QVariant &value, int role) override;
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
    void slot_GolfBoardSetPatternNearPreviewCenter(QString&);
    void slot_GolfCalculate();
    // void slot_GolfBoardStateUpdate(std::array<bool, Golf_DATASIZE>& GolfData);
    void slot_GolfBoardStateUpdate();
    void slot_GolfBoardSetPattern_blinker();
    void slot_GolfBoardSetPattern_glider();

    void slot_GolfBoardSwitchEditor();

    void slot_GolfBoardSetPreviewStartRow(int);
    void slot_GolfBoardSetPreviewStartCol(int);    
};

#endif // GOLF_BOARD_H
