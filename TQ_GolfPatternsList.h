#ifndef TQ_GOLFPATTERNSLIST_H
#define TQ_GOLFPATTERNSLIST_H

#include <QAbstractListModel>
#include <QObject>
#include "T_GolfPatternStorehouse.h"

class TQ_GolfPatternsList : public QAbstractListModel
{
    Q_OBJECT    
public:
    T_GolfPatternStorehouse& GolfStoreHouse_pattern;

    explicit TQ_GolfPatternsList(T_GolfPatternStorehouse& GolfStoreHouse_pattern, QObject *parent = nullptr);
    int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;
    // bool insertRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    // bool removeRows(int row, int count, const QModelIndex &parent = QModelIndex()) override;
    void addPattern(T_GolfPatternDescription &pt);
    void rmPattern(size_t nr);
};

#endif // TQ_GOLFPATTERNSLIST_H
