#include "edittabledialog.h"
#include "ui_edittabledialog.h"
#include <src/ertreewidget.h>
#include <QtSql/QSqlTableModel>
#include <QAction>
#include <QModelIndex>
#include <QTableView>
#include <QtSql/QSqlRecord>
#include <QStandardItemModel>
#include <QtWidgets>


edittabledialog::edittabledialog(const QString &tableName, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::edittabledialog)
{
    ui->setupUi(this);
    mActionAppendRow = new QAction(QIcon(":"), tr("Add Row"), this);
    mActionDeleteRow = new QAction(QIcon(":"), tr("Delete Row"), this);
    setWindowTitle(tableName);
    mModel = new QSqlTableModel(this);
    mModel->setEditStrategy(QSqlTableModel::OnManualSubmit);
    mModel->setTable(tableName);
    mModel->select();
    ui->tableView->setModel(mModel);
    ui->tableView->setContextMenuPolicy(Qt::ActionsContextMenu);
    ui->tableView->addActions({mActionAppendRow, mActionDeleteRow});

    connect(mActionAppendRow, &QAction::triggered, [&]() {
        mModel->insertRow(mModel->rowCount());
        mModel->submitAll();
    });
    connect(mActionDeleteRow, &QAction::triggered, [&]() {
       mModel->removeRow(ui->tableView->currentIndex().row());
    });
}
edittabledialog::~edittabledialog()
{
    delete ui;
}

void edittabledialog::on_accept_clicked()
{
    mModel->submitAll();
}

void edittabledialog::on_close_clicked()
{
    reject();
}


