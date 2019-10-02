#include "firstnestedtable.h"
#include "ui_firstnestedtable.h"
#include <src/database.h>
#include "additemfirstnestedtabledialog.h"
#include <QFileDialog>
#include <QMessageBox>
#include <QtSql/QSqlTableModel>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlDatabase>

firstNestedTable::firstNestedTable(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::firstNestedTable)
{
    ui->setupUi(this);
    mDatabase = new dataBase(this);
    mModel = nullptr;
    mModel = new QSqlTableModel(this);
    ui->tableView->setModel(mModel);
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tableView->addActions({ ui->action_AddItem,
                                ui->action_RemoveItem});
    ui->label->setText("<b>No Image Uploaded</b>");
    // setting the color of the columns
    //ui->tableView->setStyleSheet("QHeaderView::section { background-color: #646464 }");

}
firstNestedTable::~firstNestedTable()
{
    delete ui;
}

void firstNestedTable::setName(QString table)
{
    workingTable = table;

    mModel = new QSqlTableModel(this);
    mModel->setTable(workingTable);
    mModel->select();
    ui->tableView->setModel(mModel);
    ui->tableView->setItemDelegate(new ImageDelegate(this));

}

void firstNestedTable::on_actionClose_triggered()
{
    close();

}
void firstNestedTable::on_New_Database_triggered()
{
    openDataBase(SAVING);

}
void firstNestedTable::on_actionOpen_Database_triggered()
{
    openDataBase(OPENING);

}
void firstNestedTable::openDataBase(firstNestedTable::Opening opening) {
  /*  QString nameDataBase;
   if (opening == OPENING) {
       nameDataBase = QFileDialog::getOpenFileName(this,
                "Open Database", QDir::rootPath(),
                "Database (*.db);;Any type (*.*)");
   } else {
       nameDataBase = QFileDialog::getSaveFileName(this,
                "New Database", QDir::rootPath(),
                "Database (*.db);;Any type (*.*)");
   }
   if (nameDataBase.isEmpty()) {
       return;
   }
   if (!mDatabase->inizializationDataBase(nameDataBase)) {
       QMessageBox::critical(this, "Error", mDatabase->getError());
       return;
   }
   if (!mDatabase->configureDataBase()) {
       QMessageBox::critical(this, "Error", mDatabase->getError());
       return;
   }
   delete mModel;*/

   mModel = new QSqlTableModel(this);
   mModel->setTable(workingTable);
   mModel->select();
   ui->tableView->setModel(mModel);
   ui->tableView->setItemDelegate(new ImageDelegate(this));
   (void) opening;

   //ui->tableView->hideColumn(0);
   //ui->tableView->hideColumn(3);
}
void firstNestedTable::on_action_AddItem_triggered()
{
    addItemFirstNestedTableDialog d(this);
    if(d.exec() == QDialog::Rejected) {
        return;
    }

    QSqlQuery q;
    q.prepare("INSERT INTO " + workingTable + " (name, image, images, roi) VALUES (?,?,?,?)");
    q.addBindValue(d.items().name());
    q.addBindValue(d.items().image());
    q.addBindValue(d.items().imagesData());
    q.addBindValue(d.items().roi());
    bool ok = q.exec();
    if (!ok) {
        QMessageBox::critical(this, "Error", q.lastError().text());
    }

    /*if(!mDatabase->addItem(d.items())) {
        QMessageBox::critical(this, "Error", mDatabase->getError());
        return;
    }*/
    if (mModel) {
        mModel->select();
    }
}
void firstNestedTable::on_action_RemoveItem_triggered()
{
    if(!mModel) {
        return;
    }
    mModel->removeRow(ui->tableView->currentIndex().row());
    mModel->select();
}
void firstNestedTable::on_tableView_clicked(const QModelIndex &index)
{
    if(!index.isValid()) {
        return;
    }
    const int id = mModel->index(index.row(), 0).data().toInt();
    QSqlQuery q;
    q.exec(QString("SELECT bitmap FROM " + workingTable + " WHERE id = %1").arg(id));  // images
    q.next();
    QPixmap pixmap;
    if(!pixmap.loadFromData(q.value(0).toByteArray())) {
        ui->label->setText("<b>Error: no image uploaded</b>");
        return;
    }
    pixmap = pixmap.scaled(400, 400);
    ui->label->setPixmap(pixmap);
}


void firstNestedTable::on_accept_clicked()
{
    mModel->submitAll();
}

void firstNestedTable::on_close_clicked()
{
    close();
}

void firstNestedTable::on_connect_clicked()
{
//    QSqlDatabase mDatabase = QSqlDatabase::addDatabase("QMYSQL");
//    mDatabase.setHostName("localhost");
//    mDatabase.setDatabaseName("example1");
//    mDatabase.setUserName("root");
//    mDatabase.setPassword("Ballando010");
//    if (!mDatabase.open()) {
//        QMessageBox::critical(this, "Connection Error", mDatabase.lastError().text());
//        return;
//    }
//    mModel = nullptr;
//    mModel = new QSqlTableModel(this);
//    mModel->setTable("DetailExample");
//    mModel->select();
//    ui->tableView->setModel(mModel);

}

void firstNestedTable::on_disconnect_clicked()
{
    // remember to close the connection with the cloud system

}

void firstNestedTable::updateImages()
{
    int rows = mModel->rowCount(), cols = mModel->columnCount();
    int imageColumn, imagesColumn;

    for(int ic = 0; ic < cols; ic++)
    {
      if(mModel->headerData(ic, Qt::Horizontal).toString() == "image") {
          imageColumn = ic;
      }
      else if(mModel->headerData(ic, Qt::Horizontal).toString() == "images") {
          imagesColumn = ic;
      }
    }

    for(int ir=0;ir<rows;ir++)
    {
        QPixmap iconPix;
        if(!iconPix.loadFromData(mModel->data(mModel->index(ir, imagesColumn)).toByteArray())) {
        }
    }
}

void firstNestedTable::autoPopulate()
{
    QString dir = QFileDialog::getExistingDirectory(this, tr("Open Directory"),
                                                 "/home",
                                                 QFileDialog::ShowDirsOnly
                                                 | QFileDialog::DontResolveSymlinks);
    QDir imgDir(dir);
    QStringList images = imgDir.entryList(QStringList() << "*.TIF" << "*.tif",QDir::Files);
    foreach(QString filename, images) {
        QString fullName = imgDir.absoluteFilePath(filename);
        QString name=filename.split(".",QString::SkipEmptyParts).at(0);
        QString image=filename.split(".",QString::SkipEmptyParts).at(1);

        // add the separation - from the name using QSTring

        QPixmap pixmap(fullName);
        QByteArray bArray;
        QBuffer buffer(&bArray);
        buffer.open(QIODevice::WriteOnly);
        pixmap.save(&buffer, "TIFF");
        //QMessageBox::critical(this, "hi", QString(bArray.size()));

        QSqlQuery q;

        q.prepare("INSERT INTO " + workingTable + " (name, image, images, roi) VALUES (?,?,?,?)");
        q.addBindValue(fullName);
        q.addBindValue(image);
        q.addBindValue(bArray);
        q.addBindValue("roi" + name);
        bool ok = q.exec();
        if (!ok) {
            QMessageBox::critical(this, "Error", q.lastError().text());
        }
    }
    /*if(!mDatabase->addItem(d.items())) {
        QMessageBox::critical(this, "Error", mDatabase->getError());
        return;
    }*/
    if (mModel) {
        mModel->select();
    }

}


void firstNestedTable::on_actionAuto_Populate_triggered()
{
    autoPopulate();
}
