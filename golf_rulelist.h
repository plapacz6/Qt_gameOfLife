#ifndef GOLF_RULELIST_H
#define GOLF_RULELIST_H

#include <QAbstractTableModel>
#include <QObject>
#include <QTimer>
#include "T_Golf_engine.h"

extern T_Golf_engine Golf_engine;

class gOfL_ruleList : public QAbstractTableModel
{
    Q_OBJECT
    
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

#endif // GOLF_RULELIST_H
