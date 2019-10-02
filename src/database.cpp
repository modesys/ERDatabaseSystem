#include "database.h"

#include <QtSql/QSqlError>
#include <QtSql/QSqlQuery>
#include <QVariant>

#define CREATE_TABLE \
     " CREATE TABLE IF NOT EXISTS Detail" \
     " (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL" \
     ", floatTime DOUBLE NOT NULL" \
     ", version INT NOT NULL" \
     ", encoding TEXT NOT NULL)" \
     ", bitmap BLOB NOT NULL)" \
     ", colorSpace INT NOT NULL)" \
     ", imageNum INT NOT NULL)" \
     ", binX INT NOT NULL)" \
     ", binY INT NOT NULL)" \
     ", exposureVal INT NOT NULL)" \
     ", framerate DOUBLE NOT NULL)" \
     ", gainVal INT NOT NULL)" \
     ", offsetX INT NOT NULL)" \
     ", offsetY INT NOT NULL)"

dataBase::dataBase(QObject *parent) : QObject(parent)
{

}

bool dataBase::inizializationDataBase(const QString &nameDataBase) {
    mDatabase = QSqlDatabase::addDatabase("QSQLITE");
    mDatabase.setDatabaseName(nameDataBase);
    bool ok = mDatabase.open();
    if (!ok) {
        mError = mDatabase.lastError().text();
    }
    return ok;
}

bool dataBase::configureDataBase() {
    QSqlQuery q;
    bool ok = q.exec(CREATE_TABLE);
    if (!ok) {
        mError = q.lastError().text();
    }
    return ok;
}

bool dataBase::addItem(const item &items) { //addItem(std::shared_ptr(AbstractData) item)
    //item->writeDB("tableName")
    
    QSqlQuery q;
    q.prepare("INSERT INTO Detail (roi, name, images, image) VALUES (?,?,?,?)");
    //q.prepare("INSERT INTO Detail (name, image, images, roi) VALUES (?,?,?,?)");
    q.addBindValue(items.name());
    q.addBindValue(items.image());
    q.addBindValue(items.imagesData());
    q.addBindValue(items.roi());
    bool ok = q.exec();
    if (!ok) {
        mError = q.lastError().text();
    }
    return ok;
}
