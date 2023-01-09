#ifndef GOFL_BOARD_H
#define GOFL_BOARD_H

#include <QAbstractTableModel>
#include <QObject>


class gOfL_board : public QAbstractTableModel
{
    Q_OBJECT
    //MyData  //target for all reaging and writing operatotion

public:
    gOfL_board(QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // GOFL_BOARD_H
