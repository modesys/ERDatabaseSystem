#ifndef ROI_H
#define ROI_H

#include <QMainWindow>
#include <src/buttoncolumndelegate.h>

namespace Ui {
class roi;
}

class databaseRoi;
class QSqlTableModel;
class QStandardItemModel;

class roi : public QMainWindow
{
    Q_OBJECT

public:
    // this lines are added because we are clicking the opening existing database/project
    enum Opening {
        OPENING,
        SAVING,
    };


    explicit roi(QWidget *parent = nullptr);
    ~roi();

    void setName(QString table);
    void updateImages();

private slots:
    void on_closeBtn_clicked();
    void on_action_Close_triggered();
    void on_actionOpen_Database_triggered();
    void on_actionNew_Database_triggered();

    void on_actionAdd_Item_triggered();

    void on_tableView_clicked(const QModelIndex &index);

    void on_acceptBtn_clicked();
    void on_connectBtn_clicked();
    void on_disconnectBtn_clicked();

    void on_actionRemove_Item_triggered();

private:
    void openDatabase(Opening opening);



private:
    Ui::roi *ui;
    databaseRoi *mDatabaseRoi;
    QSqlTableModel *mModelRoi;
    QStandardItemModel *model;
    QString workingTableRoi;
};

#endif // ROI_H
