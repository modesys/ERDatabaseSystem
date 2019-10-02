#ifndef FIRSTNESTEDTABLE_H
#define FIRSTNESTEDTABLE_H

#include "../src/buttoncolumndelegate.h"
#include <QMainWindow>
#include <QBuffer>



namespace Ui {
class firstNestedTable;
}

class dataBase;
class QSqlTableModel;
class QSqlQueryModel;

class firstNestedTable : public QMainWindow
{
    Q_OBJECT

public:
    // this lines are added because we are clicking the opening existing database/project
    enum Opening {
        OPENING,
        SAVING,
    };

    explicit firstNestedTable(QWidget *parent = nullptr);
    ~firstNestedTable();

    void setName(QString table);
    void updateImages();

private slots:
    void on_actionClose_triggered();
    void on_New_Database_triggered();
    void on_actionOpen_Database_triggered();
    void on_accept_clicked();
    void on_close_clicked();
    void on_connect_clicked();
    void on_disconnect_clicked();

    void on_action_AddItem_triggered();
    void on_action_RemoveItem_triggered();
    void on_tableView_clicked(const QModelIndex &index);

    void on_actionAuto_Populate_triggered();
    void autoPopulate();

private:
    void openDataBase(Opening opening);

private:
    Ui::firstNestedTable *ui;
    dataBase *mDatabase;
    QSqlTableModel *mModel;
    QString workingTable;
    QSqlQueryModel *mQueryModel;
    
};

#endif // FIRSTNESTEDTABLE_H
