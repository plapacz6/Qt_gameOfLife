#include "TQ_GolfPatternsList.h"
#include "T_GolfPatternStorehouse.h"
#include <string>

using namespace std;

extern T_GolfPatternStorehouse GolfStoreHouse_pattern;

TQ_GolfPatternsList::TQ_GolfPatternsList(T_GolfPatternStorehouse& GolfStoreHouse_pattern, QObject *parent)
    :
    QAbstractListModel{parent},
    GolfStoreHouse_pattern{GolfStoreHouse_pattern}
{
}

int TQ_GolfPatternsList::rowCount(const QModelIndex &parent) const
{
    qDebug() << __PRETTY_FUNCTION__;
    return GolfStoreHouse_pattern.patterns.size();
}

QVariant TQ_GolfPatternsList::data(const QModelIndex &index, int role) const
{
    qDebug() << __PRETTY_FUNCTION__;
    if(role == Qt::DisplayRole || true) {
        string name = GolfStoreHouse_pattern.patterns[index.row()].getName();
        qDebug() << "index.row():" << index.row() << " name:" << name;
        // return QString(name.c_str());
        return QString("Row%1, Column%2")
            .arg(index.row() + 1)
            .arg(index.column() +1);
    }
    return QVariant();
}

// bool TQ_GolfPatternsList::insertRows(int row, int count, const QModelIndex &parent)
// {
//     qDebug() << __PRETTY_FUNCTION__;
//     beginInsertRows(parent, row, row + count);
//     endInsertRows();
// }

// bool TQ_GolfPatternsList::removeRows(int row, int count, const QModelIndex &parent)
// {
//     qDebug() << __PRETTY_FUNCTION__;
//     beginRemoveRows(parent, row, row + count);
//     endRemoveRows();
// }

void TQ_GolfPatternsList::addPattern(T_GolfPatternDescription &pt)
{
    qDebug() << __PRETTY_FUNCTION__;
    int newRow = GolfStoreHouse_pattern.patterns.size();
    beginInsertRows(QModelIndex(), newRow, newRow);
    GolfStoreHouse_pattern.addPattern(pt);
    endInsertRows();
}

void TQ_GolfPatternsList::rmPattern(size_t nr)
{
        qDebug() << __PRETTY_FUNCTION__;
        if(GolfStoreHouse_pattern.patterns.size() == 0 || nr >= GolfStoreHouse_pattern.patterns.size()) {
            return;
        }
        beginRemoveRows(QModelIndex(), static_cast<int>(nr), static_cast<int>(nr));
        GolfStoreHouse_pattern.rmPattern(nr);
        endRemoveRows();
}
