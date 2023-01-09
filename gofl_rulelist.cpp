#include "gofl_rulelist.h"
#include <QTimer>

gOfL_ruleList::gOfL_ruleList(QObject *parent)
    : QAbstractTableModel(parent)
    ,  timer(new QTimer(this))
{
    timer->setInterval(1000);
    connect(timer, &QTimer::timeout, this, &gOfL_ruleList::timerHit);
    timer->start();
}

void gOfL_ruleList::timerHit()
{
    QModelIndex top_row = createIndex(0,0);
    emit dataChanged(top_row, top_row, {Qt::DisplayRole});
}

int gOfL_ruleList::rowCount(const QModelIndex &parent) const
{
    return 10;
}
int gOfL_ruleList::columnCount(const QModelIndex &parent) const
{
    return 1;
}
QVariant gOfL_ruleList::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
    switch(role)
    {
    case Qt::DisplayRole :
    {
        if(row == 1 && col == 1)
        {
            return 1; //timer
        }
    }
    }
    return QVariant();
}
