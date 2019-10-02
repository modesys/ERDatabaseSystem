#ifndef NEWTABLEDIALOG_H
#define NEWTABLEDIALOG_H

#include <QDialog>
#include <src/buttoncolumndelegate.h>

namespace Ui {
class newTableDialog;
}

class QAction;

class newTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit newTableDialog(QWidget *parent = nullptr);
    ~newTableDialog();

    QString result() const;
    void setName(QString newName);

private slots:
    void on_accept_clicked();
    void on_cancel_clicked();
private:
    Ui::newTableDialog *ui;
    QAction *mActionField;
    QAction *mActionDeleteField;

    //ButtonColumnDelegate *mybutton;
};

#endif // NEWTABLEDIALOG_H
