#include "searchtable.h"
#include "ui_searchtable.h"

#include <QMessageBox>
#include <QSqlTableModel>
#include <QSqlQuery>
#include <QSqlError>
#include <QStandardItemModel>
#include <QFileDialog>
#include <QSqlDatabase>

searchTable::searchTable(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::searchTable)
{
    ui->setupUi(this);

    // Creation of the data in the search table
    mModelSearch = new QSqlTableModel(this);
    ui->tableView->setModel(mModelSearch);
    ui->ImageLabel_1->setText("<b>No Image Uploaded</b>");
    ui->ImageLabel_2->setText("<b>No Image Uploaded</b>");

    // Creation of the filter
    mFilter = new QSortFilterProxyModel(this);

    // Combo Box assignment parameters
    ui->columnComboBox->addItem("name");
    ui->columnComboBox->addItem("imageDescription");
    ui->columnComboBox->addItem("fileType");
    ui->columnComboBox->addItem("size");
    ui->columnComboBox->addItem("threeDLocation");
    ui->columnComboBox->addItem("concavity");
    ui->columnComboBox->addItem("color");
    ui->columnComboBox->addItem("image1");
    ui->columnComboBox->addItem("image2");
    ui->columnComboBox->addItem("idsearch");

    ui->columnComboBox->setCurrentIndex(0);
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setSortingEnabled(true);

    // Creation of the completer
    mCompleter = new QCompleter(this);
    mCompleter->setCaseSensitivity(Qt::CaseInsensitive);
    mCompleter->setCompletionColumn(0);
    ui->searchLineEdit->setCompleter(mCompleter);

    ui->tableView->setItemDelegate(new ImageDelegate(this));


}

searchTable::~searchTable()
{
    delete ui;
}

void searchTable::setModel(QAbstractItemModel *model)
{
    opModel = model;

    mFilter->setSourceModel(opModel);
    mFilter->setFilterCaseSensitivity(Qt::CaseInsensitive);
    mFilter->setFilterKeyColumn(-1);
    mFilter->setDynamicSortFilter(true);


    ui->tableView->setModel(mFilter);

}

void searchTable::on_searchLineEdit_textChanged(const QString &arg1)
{
    mFilter->setFilterFixedString(arg1);

    int numColumn = ui->columnComboBox->currentIndex();
    if(numColumn == 1) {
        numColumn = 1;
    }

}

void searchTable::on_columnComboBox_currentIndexChanged(int index)
{
    if(index == 3) {
        index == -1;
    }
    mFilter->setFilterKeyColumn(index);

}

void searchTable::on_pushButton_2_clicked()
{
    close();
}


void searchTable::on_pushButton_clicked()
{
    mModelSearch->submitAll();
}
