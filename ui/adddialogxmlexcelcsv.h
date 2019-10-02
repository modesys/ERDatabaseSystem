#ifndef ADDDIALOGXMLEXCELCSV_H
#define ADDDIALOGXMLEXCELCSV_H

#include <QDialog>
#include "src/insertvaluesxmlexcelcsv.h"
#include <QAbstractItemModel>

namespace Ui {
class addDialogXmlExcelCsv;
}

class addDialogXmlExcelCsv : public QDialog
{
    Q_OBJECT

public:
    explicit addDialogXmlExcelCsv(QWidget *parent = nullptr);
    ~addDialogXmlExcelCsv();
    insertValuesXmlExcelCsv getinsertValuesXmlExcelCsv() const;
    void setModel(QAbstractItemModel *model);

private slots:
    void on_buttonBox_accepted();
    void on_buttonBox_rejected();

private:
    Ui::addDialogXmlExcelCsv *ui;
    insertValuesXmlExcelCsv minsertValuesXmlExcelCsv;
    QAbstractItemModel *opModel;
};

#endif // ADDDIALOGXMLEXCELCSV_H
