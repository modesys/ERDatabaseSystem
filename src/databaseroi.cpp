#include "databaseroi.h"
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QVariant>


#define CREATE_TABLE \
    " CREATE TABLE IF NOT EXISTS roi" \
    " (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL" \
    ", size DOUBLE NOT NULL" \
    ", threeDLocation DOUBLE NOT NULL" \
    ", concavity DOUBLE NOT NULL" \
    ", color INTEGER NOT NULL" \
    ", Image_1 BLOB NOT NULL" \
    ", Image_2 BLOB NOT NULL" \
    ", Image_3 BLOB NOT NULL" \
    ", id_deployment1 INTEGER NOT NULL)"

databaseRoi::databaseRoi(QObject *parent) : QObject(parent)
{

}

bool databaseRoi::inizializationDatabaseRoi(const QString &nameDataBase) {
    mDatabase = QSqlDatabase::addDatabase("QSQLITE");
    mDatabase.setDatabaseName(nameDataBase);
    bool ok = mDatabase.open();
    if(!ok) {
        mError = mDatabase.lastError().text();
    }
    return ok;
}



bool databaseRoi::configurationDatabaseRoi() {
    QSqlQuery qry;
    bool ok = qry.exec(CREATE_TABLE);
    if(!ok) {
        mError = qry.lastError().text();
    }
    return ok;
}


bool databaseRoi::addItem(const itemRoi* item) {
    QSqlQuery qry;
    qry.prepare("INSERT INTO roi (size, threeDLocation, concavity, color, Image_1, Image_2, Image_3, iddeployment) VALUES (?,?,?,?,?,?,?,?)");
    qry.addBindValue(item->size());
    qry.addBindValue(item->threeDLocation());
    qry.addBindValue(item->concavity());
    qry.addBindValue(item->color());
    qry.addBindValue(item->imagesData1());
    qry.addBindValue(item->imagesData2());
    qry.addBindValue(item->imagesData3());
    qry.addBindValue(item->iddeployment());
    bool ok = qry.exec();
    if(!ok) {
        mError = qry.lastError().text();
    }
    return ok;
}




















