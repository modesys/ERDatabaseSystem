#include "newtabledialog.h"
#include "ui_newtabledialog.h"
#include <src/buttoncolumndelegate.h>
#include "edittabledialog.h"
#include <QAction>
#include <QComboBox>
#include <QRadioButton>
#include <QCheckBox>
#include <QPushButton>

newTableDialog::newTableDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::newTableDialog)
{
    ui->setupUi(this);
    //QHBoxLayout *l = new QHBoxLayout();
    //mybutton = new ButtonColumnDelegate(this);

    mActionField = new QAction(QIcon(":"), tr("Add"), this);
    mActionDeleteField = new QAction(QIcon(":"), tr("Remove"), this);
    ui->tableWidget->addActions({mActionField, mActionDeleteField});

    auto newComboBox = [&](QWidget *parent) {
        auto combo = new QComboBox(parent);
        combo->addItems({"INTEGER","DOUBLE","TEXT","DATE","TIME","BOOL","BLOB"});
        return combo;
    };
    connect(mActionField, &QAction::triggered, [&]() {
        //mybutton = new ButtonColumnDelegate(this);

        int rowCount = ui->tableWidget->rowCount();
        ui->tableWidget->insertRow(rowCount);
        ui->tableWidget->setCellWidget(rowCount, 1, newComboBox(this));
        //ui->tableWidget->setCellWidget(rowCount, 1, new QComboBox(this)); this will be an empty combobox
        ui->tableWidget->setCellWidget(rowCount, 2, new QRadioButton(this));
        ui->tableWidget->setCellWidget(rowCount, 3, new QCheckBox(this));
        ui->tableWidget->setCellWidget(rowCount, 4, new QCheckBox(this));
        ui->tableWidget->show();

    });
    connect(mActionDeleteField, &QAction::triggered, [&]() {
        ui->tableWidget->removeRow(ui->tableWidget->currentRow());

    });
}
newTableDialog::~newTableDialog()
{
    delete ui;
}

QString newTableDialog::result() const
{
    QString res = QString("CREATE TABLE IF NOT EXISTS %1 (").arg(ui->name->text());
    int rowCount = ui->tableWidget->rowCount();
    for (int i = 0; i<rowCount; ++i) {
        auto name = ui->tableWidget->item(i, 0)->text();   // this is the name of the Reference of the table
        auto type = static_cast <QComboBox *> (ui->tableWidget->cellWidget(i, 1))->currentText();
        bool pk = static_cast <QRadioButton *> (ui->tableWidget->cellWidget(i, 2))->isChecked();
        bool nn = static_cast <QCheckBox *> (ui->tableWidget->cellWidget(i, 3))->isChecked();
        bool ai = static_cast <QCheckBox *> (ui->tableWidget->cellWidget(i, 4))->isChecked();
        //bool detail = static_cast <QPushButton *> (ui->tableWidget->cellWidget(i,5))->isEnabled();

        res += name + " " + type;
        if (pk) {
            res += " PRIMARY KEY";
        }
        if (ai) {
            res += " AUTOINCREMENT";
        }
        if (nn) {
            res += " NOT NULL";
        }
        res += ",";
    }
    res[res.size()-1] = ')';
    return res;
}

void newTableDialog::setName(QString newName)
{
    ui->name->setText(newName);
}

void newTableDialog::on_accept_clicked()
{
    accept();

}
void newTableDialog::on_cancel_clicked()
{
    reject();
}
