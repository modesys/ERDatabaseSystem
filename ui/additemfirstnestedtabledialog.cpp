#include "additemfirstnestedtabledialog.h"
#include "ui_additemfirstnestedtabledialog.h"

#include <QFile>
#include <QMessageBox>
#include <QFileDialog>
#include <QCompleter>
#include <QFileSystemModel>

addItemFirstNestedTableDialog::addItemFirstNestedTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addItemFirstNestedTableDialog)
{
    ui->setupUi(this);
    auto fileSystemModel = new QFileSystemModel(this);
    fileSystemModel->setRootPath(QDir::rootPath());
    ui->imageLineEdit->setCompleter(new QCompleter(fileSystemModel,this));
}

addItemFirstNestedTableDialog::~addItemFirstNestedTableDialog()
{
    delete ui;
}

void addItemFirstNestedTableDialog::on_toolButton_clicked()
{
    auto dataImages = QFileDialog::getOpenFileName(this, "OpenImages", QDir::rootPath(),
                                     "Images (*.png *.jpg *jpeg *.tif *.tiff);;Any type (*.*)");
    ui->imageLineEdit->setText(dataImages);
}

void addItemFirstNestedTableDialog::on_buttonBox_accepted()
{
    QFile dataBase(ui->imageLineEdit->text());
    if(!dataBase.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", dataBase.errorString());
        return;
    }
    mItem = item(ui->nameLineEdit->text(),
                 ui->imLineEdit->text(),
                 ui->roiLineEdit->text(), dataBase.readAll());
    dataBase.close();
    accept();
}

void addItemFirstNestedTableDialog::on_buttonBox_rejected()
{
    reject();
}


