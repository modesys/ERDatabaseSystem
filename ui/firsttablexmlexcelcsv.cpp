#include "firsttablexmlexcelcsv.h"
#include "ui_firsttablexmlexcelcsv.h"
#include "adddialogxmlexcelcsv.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QFileDialog>

// Including spec for XML documents

#include <QtXml/QDomDocument>
#include <QtXml/QDomElement>


firstTableXmlExcelCSV::firstTableXmlExcelCSV(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::firstTableXmlExcelCSV)
{
    ui->setupUi(this);
    QStringList titles { "Id", "Name", "Image", "Roi"};
    ui->tableWidget->setColumnCount(titles.size());
    ui->tableWidget->setHorizontalHeaderLabels(titles);

    ui->tableWidget_2->setColumnCount(titles.size());
    ui->tableWidget_2->setHorizontalHeaderLabels(titles);

    ui->tableWidget_3->setColumnCount(titles.size());
    ui->tableWidget_3->setHorizontalHeaderLabels(titles);


}

firstTableXmlExcelCSV::~firstTableXmlExcelCSV()
{
    delete ui;
}

void firstTableXmlExcelCSV::setModel(QString table, QAbstractItemModel *model)
{
    opModel = model;
    workingTable = table;

    for(int i=0;i<opModel->rowCount();i++)
    {
        insertValuesXmlExcelCsv tempStruct;
        tempStruct.setId(opModel->data(opModel->index(i, 0)).toString());
        tempStruct.setName(opModel->data(opModel->index(i, 1)).toString());
        tempStruct.setImage(opModel->data(opModel->index(i, 2)).toString());
        tempStruct.setRoi(opModel->data(opModel->index(i, 4)).toString());
        addXmlExcelCsv(tempStruct);


    //  reference = ui->tableView->model()->data(ui->tableView->model()->index(row,column)).toString();    ///   make struct
    ///   call for struct
    }
}


void firstTableXmlExcelCSV::on_actionOpen_triggered()
{
    auto filename = QFileDialog::getOpenFileName(this, "Open database", QDir::rootPath(),
                                                 "XML file (*.xml)");
    if(filename.isEmpty()) {
        return;
    }
    QFile file(filename);
    if(!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", file.errorString());
    }
    QDomDocument doc;
    doc.setContent(&file);
    file.close();

    auto root = doc.firstChild().toElement();
    auto ix = root.firstChild().toElement();
    while (!ix.isNull()) {
        auto id = ix.attribute("id");
        auto name = ix.firstChild().toElement().text();
        auto image = ix.firstChild().nextSibling().toElement().text();
        auto roi = ix.firstChild().nextSibling().nextSibling().toElement().text();
        addXmlExcelCsv(insertValuesXmlExcelCsv(id, name, image, roi));


        ix = ix.nextSibling().toElement();
    }
}

void firstTableXmlExcelCSV::on_actionSave_As_triggered()
{
    auto filename = QFileDialog::getSaveFileName(this, "Save As", QDir::rootPath(),
                                                 "XML file (*.xml)");
    if(filename.isEmpty()) {
        return;
    }
    QDomDocument doc;
    auto root = doc.createElement("firstTry");
    doc.appendChild(root);
    const int rowCount = ui->tableWidget->rowCount();
    for(int ix = 0; ix < rowCount; ++ix) {

        insertValuesXmlExcelCsv XmlExcelCsv(ui->tableWidget->item(ix, ID)->text(),
                ui->tableWidget->item(ix, NAME)->text(),
                ui->tableWidget->item(ix, IMAGE)->text(),
                ui->tableWidget->item(ix, ROI)->text());

        auto elementXmlExcelCsv = doc.createElement("XmlFile");
        elementXmlExcelCsv.setAttribute("id", XmlExcelCsv.getId());

        auto elementName = doc.createElement("name");
        auto elementImage = doc.createElement("image");
        auto elementRoi = doc.createElement("roi");

        elementName.appendChild(doc.createTextNode(XmlExcelCsv.getName()));
        elementImage.appendChild(doc.createTextNode(XmlExcelCsv.getImage()));
        elementRoi.appendChild(doc.createTextNode(XmlExcelCsv.getRoi()));

        elementXmlExcelCsv.appendChild(elementName);
        elementXmlExcelCsv.appendChild(elementImage);
        elementXmlExcelCsv.appendChild(elementRoi);

        root.appendChild(elementXmlExcelCsv);

    }
    QFile file(filename);
    if(!file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QMessageBox::critical(this, "Error", file.errorString());
        return;
    }
    QTextStream xoutput(&file);
    xoutput << doc.toString();
    file.flush();
    file.close();
}

void firstTableXmlExcelCSV::on_actionClose_triggered()
{
    qDebug() << QString(ui->tableWidget->model()->rowCount());
    for(int i=0;i<ui->tableWidget->model()->rowCount();i++)
    {
        QPixmap img1(ui->tableWidget->model()->data(ui->tableWidget->model()->index(i, 1)).toString());
        QByteArray img1Array;
        QBuffer buffer1(&img1Array);
        buffer1.open(QIODevice::WriteOnly);
        img1.save(&buffer1, "PNG");

        QSqlQuery q;
        q.prepare("INSERT INTO " + workingTable + " (name, image, images, roi) VALUES (?,?,?,?)");
        q.addBindValue(ui->tableWidget->model()->data(ui->tableWidget->model()->index(i, 1)));
        q.addBindValue(ui->tableWidget->model()->data(ui->tableWidget->model()->index(i, 2)));
        q.addBindValue(img1Array);
        q.addBindValue(ui->tableWidget->model()->data(ui->tableWidget->model()->index(i, 3)));
        bool ok = q.exec();
        if(!ok) QMessageBox::warning(this, "Warning", q.lastError().text());



    }
    close();
}

void firstTableXmlExcelCSV::on_actionAdd_triggered()
{
    addDialogXmlExcelCsv d(this);
    if(d.exec() == QDialog::Rejected) {
        return;
    }
    addXmlExcelCsv(d.getinsertValuesXmlExcelCsv());

}

void firstTableXmlExcelCSV::on_actionRemove_triggered()
{
    // Be careful: It seems that is we remove rows in different order the others
    // are not updated...double check

    ui->tableWidget->removeRow(ui->tableWidget->currentRow());
    ui->tableWidget_2->removeRow(ui->tableWidget_2->currentRow());
    ui->tableWidget_3->removeRow(ui->tableWidget_3->currentRow());
}

void firstTableXmlExcelCSV::on_actionAuto_Populate_triggered()
{

}

void firstTableXmlExcelCSV::addXmlExcelCsv(const insertValuesXmlExcelCsv &xmlExcelCsv)
{
   if(ui->tab->isEnabled()) {
        const int row = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(row);
        ui->tableWidget->setItem(row, ID, new QTableWidgetItem(xmlExcelCsv.getId()));
        ui->tableWidget->setItem(row, NAME, new QTableWidgetItem(xmlExcelCsv.getName()));
        ui->tableWidget->setItem(row, IMAGE, new QTableWidgetItem(xmlExcelCsv.getImage()));
        ui->tableWidget->setItem(row, ROI, new QTableWidgetItem(xmlExcelCsv.getRoi()));
        } else {
        return;
        }
    if(ui->tab_2->isEnabled()) {
    const int row_2 = ui->tableWidget_2->rowCount();
    ui->tableWidget_2->insertRow(row_2);
    ui->tableWidget_2->setItem(row_2, ID, new QTableWidgetItem(xmlExcelCsv.getId()));
    ui->tableWidget_2->setItem(row_2, NAME, new QTableWidgetItem(xmlExcelCsv.getName()));
    ui->tableWidget_2->setItem(row_2, IMAGE, new QTableWidgetItem(xmlExcelCsv.getImage()));
    ui->tableWidget_2->setItem(row_2, ROI, new QTableWidgetItem(xmlExcelCsv.getRoi()));
        } else {
        return;
        }
    if(ui->tab_3->isEnabled()) {
    const int row_3 = ui->tableWidget_3->rowCount();
    ui->tableWidget_3->insertRow(row_3);
    ui->tableWidget_3->setItem(row_3, ID, new QTableWidgetItem(xmlExcelCsv.getId()));
    ui->tableWidget_3->setItem(row_3, NAME, new QTableWidgetItem(xmlExcelCsv.getName()));
    ui->tableWidget_3->setItem(row_3, IMAGE, new QTableWidgetItem(xmlExcelCsv.getImage()));
    ui->tableWidget_3->setItem(row_3, ROI, new QTableWidgetItem(xmlExcelCsv.getRoi()));
        } else {
        return;
        }
}







