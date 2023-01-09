#include "gofl_board.h"
#include <QtDebug>
#include <QBrush>
#include <QTime>

gOfL_board::gOfL_board(QObject *parent)
    : QAbstractTableModel(parent)
{
}

int gOfL_board::rowCount(const QModelIndex &parent) const
{
    return 30;
}
int gOfL_board::columnCount(const QModelIndex &parent) const
{
    return 30;
}
QVariant gOfL_board::data(const QModelIndex &index, int role) const
{
    int row = index.row();
    int col = index.column();
    //qDebug() << QString("row %1, col %2, role %3").arg(row).arg(col).arg(role);

    if(role == Qt::DisplayRole)
    {
        if(row == 0 && col == 0)
        {
            return QTime::currentTime().toString();
        }
        return QString("%1%2").arg(index.row() + 1).arg(index.column() + 1);
    }
    if(role == Qt::BackgroundRole)
    {
        if(row % 2 && (col + 1) % 2)
        {
            return QBrush(Qt::red);
        }
        else return QBrush(Qt::gray);
    }
    return QVariant();
}
/* to infrom view about data changing model send signal that indicates what
 * range of cells has changed
 */
