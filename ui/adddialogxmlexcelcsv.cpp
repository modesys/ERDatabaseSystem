#include "adddialogxmlexcelcsv.h"
#include "ui_adddialogxmlexcelcsv.h"

addDialogXmlExcelCsv::addDialogXmlExcelCsv(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addDialogXmlExcelCsv)
{
    ui->setupUi(this);
}

addDialogXmlExcelCsv::~addDialogXmlExcelCsv()
{
    delete ui;
}

insertValuesXmlExcelCsv addDialogXmlExcelCsv::getinsertValuesXmlExcelCsv() const
{
    return minsertValuesXmlExcelCsv;
}

void addDialogXmlExcelCsv::setModel(QAbstractItemModel *model)
{
    opModel = model;
}

void addDialogXmlExcelCsv::on_buttonBox_accepted()
{
    minsertValuesXmlExcelCsv.setId(ui->idLineEdit->text());
    minsertValuesXmlExcelCsv.setName(ui->nameLineEdit->text());
    minsertValuesXmlExcelCsv.setImage(ui->imageLineEdit->text());
    minsertValuesXmlExcelCsv.setRoi(ui->roiLineEdit->text());
    accept();
}

void addDialogXmlExcelCsv::on_buttonBox_rejected()
{
    reject();
}
