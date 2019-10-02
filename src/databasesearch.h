#ifndef DATABASESEARCH_H
#define DATABASESEARCH_H

#include <QObject>
#include <QSqlDatabase>
#include "itemsearch.h"

class databaseSearch : public QObject
{
    //Q_OBJECT
public:
    explicit databaseSearch(QObject *parent = nullptr);
    QString getError() const { return mError; }

    bool addItem(const itemSearch &item);

private:
    QSqlDatabase *mDatabaseSearch;
    QString mError;
};

#endif // DATABASESEARCH_H
