#ifndef ERPREFERENCESDIALOG_H
#define ERPREFERENCESDIALOG_H

#include <QDialog>
#include <QFont>

namespace Ui {
class ERPreferencesDialog;
}

class ERPreferencesDialog : public QDialog
{
    Q_OBJECT
public:
    explicit ERPreferencesDialog(QWidget *parent = nullptr);
    ~ERPreferencesDialog();

signals:
    void fontSelected(QFont);

private slots:
    void on_apply_clicked();

    void on_confirm_clicked();

private:
    Ui::ERPreferencesDialog *ui;
};

#endif // ERPREFERENCESDIALOG_H
