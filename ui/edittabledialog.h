#ifndef EDITTABLEDIALOG_H
#define EDITTABLEDIALOG_H

#include <QDialog>
#include <QtSql/QSqlTableModel>
#include <QAction>
#include <src/buttoncolumndelegate.h>


namespace Ui {
class edittabledialog;
}
class QAction;

class edittabledialog : public QDialog
{
    Q_OBJECT

public:
    explicit edittabledialog(const QString &tableName, QWidget *parent = nullptr);
    ~edittabledialog();

private slots:
    void on_accept_clicked();

    void on_close_clicked();


private:
    Ui::edittabledialog *ui;
    QSqlTableModel *mModel;
    QAction *mActionAppendRow;
    QAction *mActionDeleteRow;
    //ButtonColumnDelegate *mybutton;
    //QAction *mActionEditTable;


};

#endif // EDITTABLEDIALOG_H
