#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSql/QSqlDatabase>
#include <QTreeWidgetItem>
#include "firstnestedtable.h"
#include "roi.h"
#include "searchtable.h"
#include "firsttablexmlexcelcsv.h"
#include <QInputDialog>

namespace Ui {
class MainWindow;
}

class QSqlQueryModel;


class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

protected:
    void dragEnterEvent(QDragEnterEvent *e);
    void dragLeaveEvent(QDragLeaveEvent *e);
    void dragMoveEvent(QDragMoveEvent *e);
    void dropEvent(QDropEvent *e);



private slots:
    void on_actionOpen_Database_triggered();
    void on_actionSave_Database_triggered();
    void on_actionOpen_SQL_triggered();
    void on_actionSave_SQL_triggered();
    void on_actionPrint_triggered();
    void on_actionClose_triggered();
    void on_actionCopy_triggered();
    void on_actionErase_triggered();
    void on_actionPaste_triggered();
    void on_actionExecute_triggered();
    void on_actionPreferences_triggered();
    void on_actionManual_triggered();
    void on_actionSQLite_Search_triggered();
    void on_actionSearch_Replace_triggered();
    void on_treeWidget_clicked(const QModelIndex &index);

private:

    void connections();
    QString getSQLName(QTreeWidgetItem* root, QTreeWidgetItem* target);
    QString setSQLName(QTreeWidgetItem* root, QTreeWidgetItem* target);



    Ui::MainWindow *ui;
    QSqlDatabase mDb;
    QSqlQueryModel *mQueryModel;
    QAction* mActionJumpTo;
    QTreeWidgetItem* currentTreeItem;
    QAction* mXmlCsv;
    QAction* mSearch;

    firstNestedTable *mytable;
    roi *roitable;
    searchTable *searchtable;
    firstTableXmlExcelCSV *xmlCsvTable;
    QString curName;
};


#endif // MAINWINDOW_H
