#include "addroidialog.h"
#include "ui_addroidialog.h"

#include <QFile>
#include <QFileSystemModel>
#include <QFileDialog>
#include <QCompleter>
#include <QMessageBox>

addRoiDialog::addRoiDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::addRoiDialog)
{
//    size = 0;
//    conc = 0;
//    deploy = 0;
    //mItemRoi = new itemRoi(size, conc, "0", "0");

    ui->setupUi(this);
    auto fileSystemModel = new QFileSystemModel(this);
    fileSystemModel->setRootPath(QDir::rootPath());
    ui->img_1_LineEdit->setCompleter(new QCompleter(fileSystemModel, this));
    ui->img_2_LineEdit->setCompleter(new QCompleter(fileSystemModel, this));
    ui->img_3_LineEdit->setCompleter(new QCompleter(fileSystemModel, this));
}

addRoiDialog::~addRoiDialog()
{
    delete ui;
}

void addRoiDialog::on_toolButton_img1_clicked()
{
    auto nameDatabase = QFileDialog::getOpenFileName(this, "Open Images", QDir::rootPath(),
                                                     "Images (*.png *.jpg *jpeg *.tif *.tiff);;Any type (*.*)");
    ui->img_1_LineEdit->setText(nameDatabase);

}

void addRoiDialog::on_toolButton_img2_clicked()
{
    auto nameDatabase = QFileDialog::getOpenFileName(this, "Open Images", QDir::rootPath(),
                                                     "Images (*.png *.jpg *jpeg *.tif *.tiff);;Any type (*.*)");
    ui->img_2_LineEdit->setText(nameDatabase);
}

void addRoiDialog::on_toolButton_img3_clicked()
{
    auto nameDatabase = QFileDialog::getOpenFileName(this, "Open Images", QDir::rootPath(),
                                                     "Images (*.png *.jpg *jpeg *.tif *.tiff);;Any type (*.*)");
    ui->img_3_LineEdit->setText(nameDatabase);
}

void addRoiDialog::on_buttonBox_accepted()
{
    QPixmap img1(ui->img_1_LineEdit->text());
    QByteArray img1Array;
    QBuffer buffer1(&img1Array);
    buffer1.open(QIODevice::WriteOnly);
    img1.save(&buffer1, "PNG");

    QPixmap img2(ui->img_2_LineEdit->text());
    QByteArray img2Array;
    QBuffer buffer2(&img2Array);
    buffer2.open(QIODevice::WriteOnly);
    img2.save(&buffer2, "PNG");

    QPixmap img3(ui->img_3_LineEdit->text());
    QByteArray img3Array;
    QBuffer buffer3(&img3Array);
    buffer3.open(QIODevice::WriteOnly);
    img3.save(&buffer3, "PNG");


    mItemRoi = new itemRoi(ui->sizeLineEdit->text().toDouble(),
                       ui->threeDLineEdit->text().toDouble(),
                       ui->concavityLineEdit->text().toDouble(),
                       ui->colorLineEdit->text().toInt(),
                       ui->iddeployment_lineEdit->text().toInt(),
                       img1Array,
                       img2Array,
                       img3Array);
    accept();
}



void addRoiDialog::on_buttonBox_rejected()
{
    reject();
}
