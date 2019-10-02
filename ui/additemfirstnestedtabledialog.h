#ifndef ADDITEMFIRSTNESTEDTABLEDIALOG_H
#define ADDITEMFIRSTNESTEDTABLEDIALOG_H

#include <QDialog>
#include <src/item.h>

namespace Ui {
class addItemFirstNestedTableDialog;
}

class addItemFirstNestedTableDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addItemFirstNestedTableDialog(QWidget *parent = nullptr);
    ~addItemFirstNestedTableDialog();

    item items() const { return mItem; }



private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();
    void on_toolButton_clicked();

private:
    Ui::addItemFirstNestedTableDialog *ui;
    item mItem;
};

#endif // ADDITEMFIRSTNESTEDTABLEDIALOG_H
