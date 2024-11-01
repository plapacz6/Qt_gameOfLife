 #ifndef GOFL_BOARD_H
#define GOFL_BOARD_H

#include <QAbstractTableModel>
#include <QObject>
#include <array>
#include <QDebug>

enum {Golf_ROWS = 30, Golf_COLS = 30, Golf_DATASIZE = Golf_ROWS * Golf_COLS};

// class T_GolfData : public QObject {
//     Q_OBJECT
// public:
//     std::array<bool, Golf_DATASIZE> data;
// public:
// public slots:
//     void slot_GolfClear();
// public:
// signals:
//     void slot_GolfCleared();
//     void signal_GolfStateUpdated(std::array<bool, Golf_DATASIZE>& GolfData);
// };


class T_GolfBoard : public QAbstractTableModel
{
    Q_OBJECT

    bool editable_state;
public:
    QDebug dbg_out;
    // std::array<bool, Golf_DATASIZE> Golf_data;
    bool Golf_data[Golf_ROWS][Golf_COLS];

    T_GolfBoard(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::BackgroundRole) override; //Qt::EditRole)
    Qt::ItemFlags flags(const QModelIndex &index) const override;
    void InitData_chessboard();

public:
signals:
    // void signal_GolfBoardCalculated(std::array<bool, Golf_DATASIZE>& GolfData);
    void signal_GolfBoardCalculated();

public slots:
    void slot_GolfBoardClear();
    void slot_GolfBoardInitial();
    void slot_GolfCalculate();
    // void slot_GolfBoardStateUpdate(std::array<bool, Golf_DATASIZE>& GolfData);
    void slot_GolfBoardStateUpdate();

};

#endif // GOFL_BOARD_H
