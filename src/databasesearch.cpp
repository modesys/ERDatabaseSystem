#include "databasesearch.h"
#include <QSqlQuery>
#include <QSqlError>
#include <QVariant>

#define CREATE_TABLE \
    " CREATE TABLE IF NOT EXISTS Search" \
    " (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL" \
    ", name TEXT NOT NULL" \
    ", imageDescription TEXT NOT NULL" \
    ", fileType TEXT NOT NULL" \
    ", size DOUBLE NOT NULL" \
    ", threeDLocation DOUBLE NOT NULL" \
    ", concavity DOUBLE NOT NULL" \
    ", color INTEGER NOT NULL" \
    ", image1 BLOB NOT NULL" \
    ", image2 BLOB NOT NULL" \
    ", idsearch INTEGER NOT NULL)"


databaseSearch::databaseSearch(QObject *parent) : QObject(parent)
{

}

bool databaseSearch::addItem(const itemSearch &item) {
    QSqlQuery qry;
    qry.prepare("INSERT INTO Roi (name, imageDescription, fileType, size, threeDLocation, concavity, color, image1, image2, idsearch ) VALUES (?,?,?,?,?,?,?,?,?,?)");
    qry.addBindValue(item.name());
    qry.addBindValue(item.imageDescription());
    qry.addBindValue(item.fileType());
    qry.addBindValue(item.size());
    qry.addBindValue(item.threeDLocation());
    qry.addBindValue(item.concavity());
    qry.addBindValue(item.color());
    qry.addBindValue(item.imagesData1());
    qry.addBindValue(item.imagesData2());
    qry.addBindValue(item.idsearch());

    bool ok = qry.exec();
    if(!ok) {
        mError = qry.lastError().text();
    }
    return ok;
}
