#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <src/settings.h>
#include "findreplacedialog.h"
#include "erpreferencesdialog.h"
#include "newtabledialog.h"
#include "edittabledialog.h"
#include "firstnestedtable.h"
#include "roi.h"
#include "searchtable.h"
#include "firsttablexmlexcelcsv.h"
#include <QMessageBox>
#include <QFileDialog>
#include <QFile>
#include <QTextStream>
#include <QTreeWidgetItem>
#include <QPrintDialog>
#include <QPrinter>
#include <QPainter>
#include <QtSql/QSqlDatabase>
#include <QtSql/QSqlQuery>
#include <QtSql/QSqlError>
#include <QtSql/QSqlQueryModel>

#include <QDragEnterEvent>
#include <QDropEvent>
#include <QDragLeaveEvent>
#include <QDragMoveEvent>
#include <QMimeData>
#include <QUrl>

using TreeItem = QTreeWidgetItem;  //The line below is just a new name for the QTreeWidgetItem
using ListItem = QListWidgetItem;  //The line below is just a new name for the QListWidgetItem

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    mDb = QSqlDatabase::addDatabase("QSQLITE");
    mQueryModel = new QSqlQueryModel(this);  // initialization of the model
    //ui->tableView->setItemDelegateForColumn(5, new ButtonColumnDelegate(this));
    ui->tableView->setModel(mQueryModel);
    ui->tableView->setItemDelegate(new ImageDelegate(this));

    centralWidget()->layout()->setMargin(0);  //layout()->setMargin(0);

    auto vfont = settingsLoad(GFONT, KFONTTYPE, ui->textEdit->font());
    ui->textEdit->setFont(vfont.value<QFont>());
    setAcceptDrops(true);
    connections();
}


MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    e->accept();
}

void MainWindow::dragLeaveEvent(QDragLeaveEvent *e)
{
    e->accept();
}

void MainWindow::dragMoveEvent(QDragMoveEvent *e)
{
    e->accept();
}

void MainWindow::dropEvent(QDropEvent *e)
{
    auto infoData = e->mimeData();
    auto urls = infoData->urls();
    for (auto u : urls) {
        auto name = u.toLocalFile();
        auto baseItem = new TreeItem;
        baseItem->setIcon(0, QIcon(":database"));
        baseItem->setText(0, name);
        mDb.setDatabaseName(name);
        if (!mDb.open()) {
            QMessageBox::critical(this, "Error", QString("Database could not open: %1").arg(name));
            return;
        }
        QSqlQuery qry;
        qry.exec("SELECT tbl_name FROM sqlite_master WHERE type LIKE 'table'");
        while (qry.next()) {
            auto tablesItem = new TreeItem;
            tablesItem->setIcon(0, QIcon(":table"));
            tablesItem->setText(0, qry.value(0).toString());
            qry.value(0).toString();
            baseItem->addChild(tablesItem);
        }
        ui->treeWidget->addTopLevelItem(baseItem);
    }
}

void MainWindow::on_actionOpen_Database_triggered()
{
    auto name = QFileDialog::getOpenFileName(this, "Open Database",
                                            QDir::currentPath(),
                                             "Database (*.db);;" \
                                             "Any type (*.*);;" \
                                             "Text (*)");
    if (name.isEmpty())
        return;
    auto baseItem = new TreeItem;
    baseItem->setIcon(0, QIcon(":database"));
    baseItem->setText(0, name);
    mDb.setDatabaseName(name);
    if (!mDb.open()) {
        QMessageBox::critical(this, "Error", QString("Database could not open: %1").arg(name));
        return;
    }

    // Loop 1: find top-level tables
    QSqlQuery qry;
    qry.exec("SELECT tbl_name FROM sqlite_master WHERE type LIKE 'table'");
    while (qry.next()) {
        QStringList subtest = qry.value(0).toString().split('_');

        if(subtest.length() == 1) {
            auto tablesItem = new TreeItem;
            tablesItem->setIcon(0, QIcon(":table"));
            tablesItem->setText(0, qry.value(0).toString());
            baseItem->addChild(tablesItem);
        }
    }

    // Loop 2: find topper-level tables
    qry.exec("SELECT tbl_name FROM sqlite_master WHERE type LIKE 'table'");
    while (qry.next()) {
        QStringList subtest = qry.value(0).toString().split('_');
        QString name;

        if(subtest.length() == 2) {
            QTreeWidgetItem *child = NULL;

            for (int i = 0; i < baseItem->childCount(); i++)
            {
                if(baseItem->child(i)->text(0) == subtest.at(0))
                {
                    child = baseItem->child(i);
                    break;
                }
            }

            name = subtest.at(1);

            if(child==NULL) {
                //QMessageBox::warning(this, "Error", QString("Parent not found for: %1").arg(qry.value(0).toString()));
                child = baseItem;
                //name = tablesItem; modified on 16 February
                name = qry.value(0).toString();

            }

            auto tablesItem = new TreeItem;
            tablesItem->setIcon(0, QIcon(":table"));
            tablesItem->setText(0, name);
            child->addChild(tablesItem);
        }
    }

    // Loop 3: find toppest-level tables
    qry.exec("SELECT tbl_name FROM sqlite_master WHERE type LIKE 'table'");
    while (qry.next()) {
        QStringList subtest = qry.value(0).toString().split('_');

        if(subtest.length() == 3) {
            QTreeWidgetItem *child = NULL;
            QString name;

            for (int i = 0; i < baseItem->childCount(); i++)
            {
                for (int j = 0; j < baseItem->child(i)->childCount(); j++)
                {
                    if(baseItem->child(i)->text(0) == subtest.at(0) && baseItem->child(i)->child(j)->text(0) == subtest.at(1))
                    {
                        child = baseItem->child(i)->child(j);
                        break;
                    }
                }
            }

            name = subtest.at(2);

            if(child==NULL) {
                //QMessageBox::warning(this, "Error", QString("Parent not found for: %1").arg(qry.value(0).toString()));
                child = baseItem;
                //name = table;
                name = qry.value(0).toString();
            }

            auto tablesItem = new TreeItem;
            tablesItem->setIcon(0, QIcon(":table"));
            tablesItem->setText(0, name);
            child->addChild(tablesItem);
        }
    }

    ui->treeWidget->addTopLevelItem(baseItem);
}

void MainWindow::on_actionSave_Database_triggered()
{
    auto name = QFileDialog::getSaveFileName(this, "Save Database",
                                            QDir::currentPath(),
                                             "Database (*.db);;" \
                                             "Any type (*.*);;" \
                                             "Text (*)");
    if (name.isEmpty())
        return;
    auto baseItem = new TreeItem;
    baseItem->setIcon(0, QIcon(":database"));
    baseItem->setText(0, name);
    ui->treeWidget->addTopLevelItem(baseItem);
    mDb.setDatabaseName(name);
    if (!mDb.open()) {
        QMessageBox::critical(this, "Error", QString("Database could not be saved: %1").arg(name));
    }
}

void MainWindow::on_actionOpen_SQL_triggered()
{
    auto name = QFileDialog::getOpenFileName(this, "Open SQL",
                                             QDir::currentPath(),
                                             "SQL (*.sql);;" \
                                             "Any type (*.*);;" \
                                             "Text (*)");
    if (name.isEmpty())
        return;
    QFile F(name);
    if (!F.open(QIODevice::Text | QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", QString("file is not opening: %1").arg(F.errorString()));
        return;
    }
    QTextStream S(&F);
    ui->textEdit->setText(S.readAll());
    F.close();
}

void MainWindow::on_actionSave_SQL_triggered()
{
    auto name = QFileDialog::getSaveFileName(this, "Save SQL",
                                             QDir::currentPath(),
                                             "SQL (*.sql);;" \
                                             "Any type (*.*);;" \
                                             "Text (*)");
    if (name.isEmpty())
        return;
    QFile F(name);
    if (!F.open(QIODevice::Text | QIODevice::WriteOnly)) {
        QMessageBox::critical(this, "Error", QString("file not saved: %1").arg(F.errorString()));
        return;
    }
    QTextStream S(&F);
    S << ui->textEdit->toPlainText(); // "<< ui..." we are writing the entire content of the testEdit and passing it to PlainText
    F.flush();  // cleaning is usually used when we are writing inside an archive
    F.close();
}

void MainWindow::on_actionPrint_triggered()
{
    QPrintDialog P(this);
    if (P.exec() == QDialog::Rejected) {
        return;
    }
    ui->textEdit->print(P.printer());   // change directory for printing on Desktop
    /*  For now do not include this function
    QPrinter printer;
        printer.setOutputFormat(QPrinter::PdfFormat);
        printer.setOutputFileName("/foobar/nonwritable.pdf");
        QPainter painter;
        if (! painter.begin(&printer)) { // failed to open file
            qWarning("failed to open file, is it writable?");
            return;
        }
        painter.drawText(10, 10, "Test");
        if (! printer.newPage()) {
            qWarning("failed in flushing page to disk, disk full?");
            return;
        }
        painter.drawText(10, 10, "Test 2");
        painter.end();
    */
}

void MainWindow::on_actionClose_triggered()
{
    close();
}

void MainWindow::on_actionCopy_triggered()
{
    ui->textEdit->copy();
}

void MainWindow::on_actionErase_triggered()
{
    ui->textEdit->cut();
}

void MainWindow::on_actionPaste_triggered()
{
    ui->textEdit->paste();
}

void MainWindow::on_actionExecute_triggered()
{
    auto sql = ui->textEdit->toPlainText();
    if (sql.startsWith("select", Qt::CaseInsensitive)) {
        mQueryModel->setQuery(sql);
    } else if (sql.startsWith("create table", Qt::CaseInsensitive)) {
        QSqlQuery qry;
        if (!qry.exec(sql)) {
            QMessageBox::warning(this, "Warning", qry.lastError().text());
            ui->listWidget->addItem(new ListItem(QIcon(":not_working"), sql));
            return;  
        }

        ui->listWidget->addItem(new ListItem(QIcon(":working"), sql));
        // We need to understand what is the actual database
        auto base = mDb.databaseName();
        int i, tam = ui->treeWidget->topLevelItemCount();
        for (i = 0; i < tam; ++i) {

        if (ui->treeWidget->topLevelItem(i)->text(0).toLower() == base.toLower()) {
            break;
          }
        }
        auto baseItem = ui->treeWidget->topLevelItem(i);
        auto createTable = QString("create table ");
        if (sql.contains("if not exists", Qt::CaseInsensitive)) {
            createTable = QString("create table if not exists ");
        }
        // Searching the name of the table

        int pos1 = createTable.size();
        int pos2 = sql.indexOf("(", pos1);
        auto table = sql.mid(pos1, pos2-pos1);
        table = table.mid(0, table.indexOf(" "));
        tam = baseItem->childCount();
        for (i = 0; i < tam; ++i) {
            if (baseItem->child(i)->text(0).toLower() == table.toLower()) {
                return;
            }
        }

        //QMessageBox::warning(this, "Error", QString("Looking to place: %1").arg(qry.lastQuery()));

        QStringList subtest = table.split('_');

        if(subtest.length() == 1) {
            auto tablesItem = new TreeItem;
            tablesItem->setIcon(0, QIcon(":table"));
            tablesItem->setText(0, table);
            baseItem->addChild(tablesItem);
        }
        else if(subtest.length() == 2) {
            QTreeWidgetItem *child = NULL;

            for (int i = 0; i < baseItem->childCount(); i++)
            {
                if(baseItem->child(i)->text(0) == subtest.at(0))
                {
                    child = baseItem->child(i);
                    break;
                }
            }

            if(child==NULL) QMessageBox::critical(this, "Error", QString("Parent not found for: %1").arg(qry.value(0).toString()));

            auto tablesItem = new TreeItem;
            tablesItem->setIcon(0, QIcon(":table"));
            tablesItem->setText(0, subtest.at(1));
            child->addChild(tablesItem);
        }
        else if(subtest.length() == 3) {
            QTreeWidgetItem *child = NULL;
            QString name;

            for (int i = 0; i < baseItem->childCount(); i++)
            {
                for (int j = 0; j < baseItem->child(i)->childCount(); j++)
                {
                    if(baseItem->child(i)->text(0) == subtest.at(0) && baseItem->child(i)->child(j)->text(0) == subtest.at(1))
                    {
                        child = baseItem->child(i)->child(j);
                        break;
                    }
                }
            }

            name = subtest.at(2);

            if(child==NULL) {
                //QMessageBox::warning(this, "Error", QString("Parent not found for: %1").arg(qry.value(0).toString()));
                child = baseItem;
                name = table;
                //name = table;// modified february
            }

            auto tablesItem = new TreeItem;
            tablesItem->setIcon(0, QIcon(":table"));
            tablesItem->setText(0, name);
            child->addChild(tablesItem);
        }


    } else if (sql.startsWith("drop table", Qt::CaseInsensitive)) {

        QSqlQuery qry;
        if (!qry.exec(sql)) {
            ui->listWidget->addItem(new ListItem(QIcon(":not_working"), sql));

            return;
        }
        ui->listWidget->addItem(new ListItem(QIcon(":working"), sql));

        // We need to understand what is the actual database
        auto base = mDb.databaseName();
        int i, tam = ui->treeWidget->topLevelItemCount();
        for (i = 0; i < tam; ++i) {
            if (ui->treeWidget->topLevelItem(i)->text(0).toLower() == base.toLower()) {
            break;
            }
        }
        auto baseItem = ui->treeWidget->topLevelItem(i);
        tam = baseItem->childCount();

        //how do we know the value of the name of the table ?

        auto droptable = QString("drop table");
        auto table = sql.mid(droptable.size());
        table = table.mid(1);    // mid(1) will allow to avoid the first charachter

        for (i = 0; i < tam; ++i) {
            if (baseItem->child(i)->text(0).toLower() == table.toLower()) {
                break;
            }
        }

        currentTreeItem->parent()->removeChild(currentTreeItem);   // this is to remove a table

    } else {
        QSqlQuery qry;
        if (!qry.exec(sql)) {
            ui->listWidget->addItem(new ListItem(QIcon(":not_working"), sql));

            return;
        }
        ui->listWidget->addItem(new ListItem(QIcon(":working"), sql));

    }
}

void MainWindow::on_actionPreferences_triggered()  // connecting the Preference Dialogue window
{
    ERPreferencesDialog p(this);
    connect(&p, &ERPreferencesDialog::fontSelected, [&](const QFont &f) {
        ui->textEdit->setFont(f);
        settingsSave(GFONT, KFONTTYPE, f);
        // save(GFONT, KFONTSIZE, f.pointSizeF());
    });
    p.exec();
}

void MainWindow::on_actionManual_triggered()
{
    // Manual on how to use this Local Database Management System need to be written

}

void MainWindow::on_actionSQLite_Search_triggered()
{
    QMessageBox::about(this, "ERDatabaseSystem" ,

                       "Date: in progress\n" \
                       "Project: ERDatabaseSystem");
}

void MainWindow::on_actionSearch_Replace_triggered()
{
    FindReplaceDialog F(this);
    F.setTextEdit(ui->textEdit);
    F.exec();
}


void MainWindow::on_treeWidget_clicked(const QModelIndex &index)
// This is used to actively select the database we would like to work on if we have several database opened
// at the same time
{

    if (index.parent().isValid()) {
            return;
    }

    auto name = index.data().toString();
    mDb.setDatabaseName(name);
    if (!mDb.open()) {
        QMessageBox::critical(this, "Error", QString("Database could not be opened: %1").arg(name));
    }

  }

void MainWindow::connections() {

connect(ui->treeWidget, &ERTreeWidget::newTable, [&]() {
    if (ui->treeWidget->type() == ERTreeWidget::BASE) {
        newTableDialog D(this);
        if (D.exec() == QDialog::Rejected) {
            return;
        }
        // We need to add the code to generate the present table
        ui->textEdit->setPlainText(D.result());

    } else {
        QMessageBox::warning(this, "Warning", "This function is allowed only when a database is selected");
    }
});

connect(ui->treeWidget, &ERTreeWidget::newReferenceTable, [&]() {
    if (ui->treeWidget->type() == ERTreeWidget::BASE) {
        QString nameAf = QInputDialog::getText(this, "Table Name", "Enter table name");
        ui->textEdit->setPlainText("CREATE TABLE IF NOT EXISTS " + nameAf + " (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,name TEXT,latitude DOUBLE,longitude DOUBLE,reference TEXT)");

    } else {
        QMessageBox::warning(this, "Warning", "This function is allowed only when a database is selected");
    }
});

connect(ui->treeWidget, &ERTreeWidget::removeTable, [&]() {
    if(ui->treeWidget->type() == ERTreeWidget::TABLE) {
       ui->textEdit->setPlainText(QString("DROP TABLE %1").arg(getSQLName(ui->treeWidget->topLevelItem(0), ui->treeWidget->currentItem())));
           return;
    } else {
        QMessageBox::warning(this, "Warning", "This function is allowed only when a table is selected");
    }
});

connect(ui->treeWidget, &ERTreeWidget::selectFrom, [&]() {
    if(ui->treeWidget->type() == ERTreeWidget::TABLE) {

       curName = getSQLName(ui->treeWidget->topLevelItem(0), ui->treeWidget->currentItem());

       ui->textEdit->setPlainText(QString("SELECT * FROM %1").arg(curName));
       currentTreeItem = ui->treeWidget->currentItem();
       //return;

    } else {
        QMessageBox::warning(this, "Warning", "This function is allowed only when a table is selected");
    }
});

connect(ui->treeWidget, &ERTreeWidget::removeDatabase, [&]() {
    if(ui->treeWidget->type() == ERTreeWidget::BASE) {
       delete ui->treeWidget->currentItem();
    } else {
        QMessageBox::warning(this, "Warning", "This function is allowed only when a database is selected");
    }
});

connect(ui->treeWidget, &ERTreeWidget::editTable, [&]() {
    if(ui->treeWidget->type() == ERTreeWidget::TABLE) {
        edittabledialog D(getSQLName(ui->treeWidget->topLevelItem(0), ui->treeWidget->currentItem()), this);
            D.exec();
    } else {
        QMessageBox::warning(this, "Warning", "This function is allowed only when a table is selected");
    }
});

// Creating the action menu on the creation of the table in order to create the nested table
// The first nested table that will be created in the summary table

mActionJumpTo = new QAction(QIcon(":"), tr("Add table"), this);

// Modified on March 15 with the following features:
// Added two additional functionalities: the search table for specific requests
// And added the XML-CSV editor for saving and uploading different data set

mSearch = new QAction(QIcon(":"), tr("Search table"), this);
mXmlCsv = new QAction(QIcon(":"), tr("Go to XML-CSV file editor"), this);

ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
ui->tableView->addActions({mActionJumpTo});
ui->tableView->addActions({mSearch});
ui->tableView->addActions({mXmlCsv});
ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
ui->tableView->setSelectionMode(QAbstractItemView::SingleSelection);

//ui->tableView->setSelectionBehavior(QAbstractItemView::SelectColumns);

connect(mActionJumpTo, &QAction::triggered, [&]() {
    int row = -1, column = -1;
    QString reference;
    QString type;

    for(int i = 0; i < ui->tableView->model()->columnCount(); i++)
    {
      if(ui->tableView->model()->headerData(i, Qt::Horizontal).toString() == "reference") {
          column = i;
          type = "reference";
      }
      else if(ui->tableView->model()->headerData(i, Qt::Horizontal).toString() == "roi") {
          column = i;
          type = "roi";
      }
    }

    QModelIndexList selection = ui->tableView->selectionModel()->selectedRows();


    if (selection.count() > 0) {
        QModelIndex index = selection.at(0);
        row = index.row();
    }

    if(row < 0 || column < 0)
    {
        QMessageBox::warning(this, "Reference", "Data not found!");
    }
    else {
        reference = ui->tableView->model()->data(ui->tableView->model()->index(row,column)).toString();

        if(reference == "NO ROI")
            return;

        //QMessageBox::warning(this, "Reference", "Add table at " + QString::number(row) + " to " + reference);

        QTreeWidgetItem *child = NULL;

        for (int i = 0; i < currentTreeItem->childCount(); i++)
        {
            if(currentTreeItem->child(i)->text(0) == reference)
            {
                child = currentTreeItem->child(i);
                break;
            }
        }

        QString nameAf = (type=="reference")?QString(currentTreeItem->text(0) + "_" + reference)
                                           : QString(currentTreeItem->parent()->text(0) + "_" + currentTreeItem->text(0) + "_" + reference);

        if(child==NULL)
        {
            if(type == "reference") {
//                QString nameBf = QInputDialog::getText(this, "Table Name", "Enter table name");

//                ui->tableView->model()->setData(ui->tableView->model()->index(row,column), nameBf);

                //QSqlQuery q("UPDATE " + currentTreeItem->text(0) + " SET reference = \'" + nameBf + "\' WHERE reference = """);

                //QMessageBox::warning(this, "Warning", q.lastError().text());

                ui->textEdit->setPlainText("CREATE TABLE IF NOT EXISTS " + /*currentTreeItem->text(0) + "_" + */nameAf + " (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,name TEXT,image TEXT,images BLOB,roi TEXT)");
            } else if(type == "roi") {
                ui->textEdit->setPlainText("CREATE TABLE IF NOT EXISTS " + nameAf + " (id INTEGER PRIMARY KEY AUTOINCREMENT NOT NULL,size DOUBLE,threeDlocation DOUBLE,concavity DOUBLE,color DOUBLE,image_1 BLOB,image_2 BLOB,image_3 BLOB,id_deployment INTEGER)");

            } else {
                newTableDialog D(this);
                D.setName(nameAf);
                if (D.exec() == QDialog::Rejected) {
                    return;
                }
                ui->textEdit->setPlainText(D.result());
            }
        }
        else {
            if(type == "reference") {
                mytable = new firstNestedTable(this);
                mytable->setName(nameAf);
                mytable->show();
            } else {
                roitable = new roi(this);
                roitable->setName(nameAf);
                roitable->show();
            }
        }
    }

});

// Adding the connection for the search table - added on March 15
connect(mSearch, &QAction::triggered, [&]() {
    searchtable = new searchTable(this);
    searchtable->setModel(ui->tableView->model());
    searchtable->show();
});

// Adding the connection for the XML-CSV file editor - added on March 15
// put down here the XML and CSV editor designed
connect(mXmlCsv, &QAction::triggered, [&]() {
    xmlCsvTable = new firstTableXmlExcelCSV(this);
    xmlCsvTable->setModel(curName, ui->tableView->model());
    xmlCsvTable->show();
});

}


QString MainWindow::getSQLName(QTreeWidgetItem* root, QTreeWidgetItem* target)
{
    if(root == target->parent())
    {
        return target->text(0);
    }
    else if(root == target->parent()->parent()){
        return QString(target->parent()->text(0) + "_" + target->text(0));
    }
    else {
        return QString(target->parent()->parent()->text(0) + "_" + target->parent()->text(0) + "_" + target->text(0));
    }

}


/*QString MainWindow::setSQLName(QTreeWidgetItem* root, QTreeWidgetItem* target)
{
    if(root == target->parent())
    {
        return target->text(i);
    }
    else if(root == target->parent()->parent()){
        return QString(target->parent()->text(i) + "_" + target->text(i));
    }

}*/
