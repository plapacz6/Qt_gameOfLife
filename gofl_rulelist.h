#ifndef GOFL_RULELIST_H
#define GOFL_RULELIST_H

#include <QAbstractTableModel>
#include <QObject>
#include <QTimer>

class gOfL_ruleList : public QAbstractTableModel
{
    Q_OBJECT
    QTimer *timer;
public:
    gOfL_ruleList(QObject *parent = nullptr);
    void timerHit();

    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;


//    gOfL_board(QObject *parent = nullptr);
//    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
//    int columnCount(const QModelIndex &parent = QModelIndex()) const override;
//    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
};

#endif // GOFL_RULELIST_H
