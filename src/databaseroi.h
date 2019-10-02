#ifndef DATABASEROI_H
#define DATABASEROI_H

#include <QObject>
#include <QtSql/QSqlDatabase>
#include "itemroi.h"


class databaseRoi : public QObject
{
    Q_OBJECT
public:
    explicit databaseRoi(QObject *parent = nullptr);
    bool inizializationDatabaseRoi(const QString &nameDataBase);
    bool configurationDatabaseRoi();
    QString getError() const { return mError; }
    bool addItem(const itemRoi* item);


private:
    QSqlDatabase mDatabase;
    QString mError;




};

#endif // DATABASEROI_H
