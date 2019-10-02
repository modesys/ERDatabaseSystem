#include "erpreferencesdialog.h"
#include "ui_erpreferencesdialog.h"
#include <src/settings.h>

ERPreferencesDialog::ERPreferencesDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ERPreferencesDialog)
{
    ui->setupUi(this);
    auto vfont = settingsLoad(GFONT, KFONTTYPE);
    ui->fontComboBox->setCurrentFont(vfont.value<QFont>());   // void setCurrentFont(const QFont &f);
    ui->doubleSpinBox->setValue(vfont.value<QFont>().pointSizeF());

}

ERPreferencesDialog::~ERPreferencesDialog()
{
    delete ui;
}

void ERPreferencesDialog::on_apply_clicked()
{
    auto f = ui->fontComboBox->currentFont();
    f.setPointSizeF(ui->doubleSpinBox->value());
    emit fontSelected(f);
}

void ERPreferencesDialog::on_confirm_clicked()
{
    on_apply_clicked();
    accept();
}

