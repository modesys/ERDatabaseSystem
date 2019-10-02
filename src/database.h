#ifndef DATABASE_H
#define DATABASE_H

#include <QObject>
//#include <QSqlDatabase>
#include <QSqlDatabase>
#include "item.h"

class dataBase : public QObject
{
    Q_OBJECT
public:
    explicit dataBase(QObject *parent = nullptr);
    bool inizializationDataBase(const QString &nameDataBase);
    bool configureDataBase();
    QString getError() const {return mError;}
    bool addItem(const item &items);


private:
    QSqlDatabase mDatabase;
    QString mError;

};

#endif // DATABASE_H
