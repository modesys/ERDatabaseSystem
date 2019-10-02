#include "roi.h"
#include "ui_roi.h"
#include <src/databaseroi.h>
#include "addroidialog.h"
#include <src/itemroi.h>
#include <QMessageBox>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QStandardItemModel>
#include <QFileDialog>



roi::roi(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::roi)
{
    ui->setupUi(this);
    mDatabaseRoi = new databaseRoi(this);
    mModelRoi = nullptr;
    mModelRoi = new QSqlTableModel(this);
    ui->tableView->setModel(mModelRoi);
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tableView->addActions({ ui->actionAdd_Item,
                                ui->actionRemove_Item});
    ui->label->setText("<b>No image_1 uploaded</b>");
    ui->label_2->setText("<b>No image_2 uploaded</b>");
    ui->label_3->setText("<b>No image_3 uploaded</b>");
}

roi::~roi()
{
    delete ui;
}


void roi::setName(QString table)
{
    workingTableRoi = table;

    mModelRoi = new QSqlTableModel(this);
    mModelRoi->setTable(workingTableRoi);
    mModelRoi->select();
    ui->tableView->setModel(mModelRoi);
    ui->tableView->setItemDelegate(new ImageDelegate(this));
}

void roi::on_actionNew_Database_triggered()
{
    openDatabase(SAVING);
}

void roi::on_actionOpen_Database_triggered()
{
    openDatabase(OPENING);

}

void roi::openDatabase(roi::Opening opening) {
    /*QString nameDatabase;
    if(opening == OPENING) {
        nameDatabase = QFileDialog::getOpenFileName(this,
                                                    "Open Database", QDir::rootPath(),
                                                    "Database (*.db);;Any type (*.*)");
    } else {
        nameDatabase = QFileDialog::getSaveFileName(this,
                                                    "New Database", QDir::rootPath(),
                                                    "Database (*.db);;Any type (*.*)");
    }

    if (nameDatabase.isEmpty()) {
        return;
    }
    if(!mDatabaseRoi->inizializationDatabaseRoi(nameDatabase)) {
         QMessageBox::critical(this, "Error", mDatabaseRoi->getError());
         return;
    }
    if(!mDatabaseRoi->configurationDatabaseRoi()) {
        QMessageBox::critical(this, "Error", mDatabaseRoi->getError());
        return;
    }
    delete mModelRoi; */

    mModelRoi = new QSqlTableModel(this);
    mModelRoi->setTable(workingTableRoi);
    mModelRoi->select();
    ui->tableView->setModel(mModelRoi);
    ui->tableView->setItemDelegate(new ImageDelegate(this));
    (void) opening;

}


void roi::on_actionAdd_Item_triggered()
{
    addRoiDialog d(this);
    if(d.exec() == QDialog::Rejected) {
        return;
    }

    QSqlQuery q;
    q.prepare("INSERT INTO " + workingTableRoi + " (size, threeDLocation, concavity, color, image_1, image_2, image_3, id_deployment) VALUES (?,?,?,?,?,?,?,?)");
    q.addBindValue(d.item()->size());
    q.addBindValue(d.item()->threeDLocation());
    q.addBindValue(d.item()->concavity());
    q.addBindValue(d.item()->color());
    q.addBindValue(d.item()->imagesData1());
    q.addBindValue(d.item()->imagesData2());
    q.addBindValue(d.item()->imagesData3());
    q.addBindValue(d.item()->iddeployment());
    bool ok = q.exec();
    if (!ok) {
        QMessageBox::critical(this, "Error", q.lastError().text());
    }



//    if(!mDatabaseRoi->addItem(d.item())) {
//        QMessageBox::critical(this, "Error", mDatabaseRoi->getError());
//    }
    if(mModelRoi) {
        mModelRoi->select();
    }
}

void roi::on_actionRemove_Item_triggered()
{
    if(!mModelRoi) {
        return;
    }
    mModelRoi->removeRow(ui->tableView->currentIndex().row());
    mModelRoi->select();
}


void roi::on_tableView_clicked(const QModelIndex &index)
{
    if(!index.isValid()) {
        return;
    }
    const int id = mModelRoi->index(index.row(), 0).data().toInt();
    QSqlQuery q;
    q.exec(QString("SELECT image_1, image_2, image_3 FROM " + workingTableRoi + " WHERE id = %1").arg(id));
    q.next();
    QPixmap pixmap;
    if(!pixmap.loadFromData(q.value(0).toByteArray())) {
        ui->label->setText("<b>Error: no image uploaded</b>");
        ui->label_2->setText("<b>Error: no image uploaded</b>");
        ui->label_3->setText("<b>Error: no image uploaded</b>");
        return;
    }
    pixmap = pixmap.scaled(200, 200);
    ui->label->setPixmap(pixmap);
    ui->label_2->setPixmap(pixmap);
    ui->label_3->setPixmap(pixmap);
}

void roi::on_acceptBtn_clicked()
{
    mModelRoi->submitAll();

}
void roi::on_closeBtn_clicked()
{
    close();
}

void roi::on_action_Close_triggered()
{
    close();
}

void roi::on_connectBtn_clicked()
{
//    QSqlDatabase mDatabase = QSqlDatabase::addDatabase("QMYSQL");
//    mDatabase.setHostName("localhost");
//    mDatabase.setDatabaseName("Example1");
//    mDatabase.setUserName("root");
//    mDatabase.setPassword("Ballando010");
//    if (!mDatabase.open()) {
//    QMessageBox::critical(this, "Connection Error", mDatabase.lastError().text());
//    return;
//    }
//    mModelRoi = nullptr;
//    mModelRoi = new QSqlTableModel(this);
//    mModelRoi->setTable("Example1");
//    mModelRoi->select();
//    ui->tableView->setModel(mModelRoi);
}

void roi::on_disconnectBtn_clicked()
{
     // remember to close the connection with the cloud system

}

void roi::updateImages()
{
    int rows = mModelRoi->rowCount(), cols = mModelRoi->columnCount();
    int imageColumn, imagesColumn;

    for(int ic = 0; ic < cols; ic++)
    {
      if(mModelRoi->headerData(ic, Qt::Horizontal).toString() == "Image_1") {
          imageColumn = ic;
      }

      else if(mModelRoi->headerData(ic, Qt::Horizontal).toString() == "Image_2") {
          imagesColumn = ic;
      }

      else if(mModelRoi->headerData(ic, Qt::Horizontal).toString() == "Image_3") {
          imagesColumn = ic;
    }
    }

    for(int ir=0;ir<rows;ir++)
    {
        QPixmap iconPix;
        if(!iconPix.loadFromData(mModelRoi->data(mModelRoi->index(ir, imagesColumn)).toByteArray())) {
        }
    }
}




















