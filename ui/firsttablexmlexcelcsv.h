#ifndef FIRSTTABLEXMLEXCELCSV_H
#define FIRSTTABLEXMLEXCELCSV_H

#include <QMainWindow>
#include "src/insertvaluesxmlexcelcsv.h"
#include <QAbstractItemModel>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QBuffer>

namespace Ui {
class firstTableXmlExcelCSV;
}

class firstTableXmlExcelCSV : public QMainWindow
{
    Q_OBJECT

public:
    explicit firstTableXmlExcelCSV(QWidget *parent = nullptr);
    ~firstTableXmlExcelCSV();
    void setModel(QString table, QAbstractItemModel *model);

private slots:
    void on_actionOpen_triggered();
    void on_actionSave_As_triggered();
    void on_actionClose_triggered();
    void on_actionAdd_triggered();
    void on_actionRemove_triggered();
    void on_actionAuto_Populate_triggered();

private:
    enum {
        ID,
        NAME,
        IMAGE,
        ROI
    };

    Ui::firstTableXmlExcelCSV *ui;
    void addXmlExcelCsv(const insertValuesXmlExcelCsv &xmlExcelCsv);
    QAbstractItemModel *opModel;
    QString workingTable;
};

#endif // FIRSTTABLEXMLEXCELCSV_H
