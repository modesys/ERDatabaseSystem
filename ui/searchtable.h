#ifndef SEARCHTABLE_H
#define SEARCHTABLE_H

#include <QMainWindow>
#include <QDialog>
#include <QSqlRelationalTableModel>
#include <QSortFilterProxyModel>
#include <QSqlRelationalDelegate>
#include <QCompleter>
#include "src/buttoncolumndelegate.h"

namespace Ui {
class searchTable;
}

class databaseSearch;
class QSqlTableModel;
class QStandardItemModel;

class searchTable : public QMainWindow
{
    Q_OBJECT

public:
    explicit searchTable(QWidget *parent = nullptr);
    ~searchTable();
    void setModel(QAbstractItemModel *model);

private slots:
    void on_searchLineEdit_textChanged(const QString &arg1);
    void on_columnComboBox_currentIndexChanged(int index);
    void on_pushButton_2_clicked();
    void on_pushButton_clicked();

private:
    Ui::searchTable *ui;
    databaseSearch *mDatabaseSearch;
    QSqlTableModel *mModelSearch;
    QStandardItemModel *searchModel;
    QSqlRelationalTableModel *mRelation;
    QSortFilterProxyModel *mFilter;
    QCompleter *mCompleter;

    QAbstractItemModel *opModel;
};

#endif // SEARCHTABLE_H
