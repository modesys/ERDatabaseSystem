#ifndef ADDROIDIALOG_H
#define ADDROIDIALOG_H
#include <QDialog>
#include <src/itemroi.h>
#include <QBuffer>


namespace Ui {
class addRoiDialog;
}

class addRoiDialog : public QDialog
{
    Q_OBJECT

public:
    explicit addRoiDialog(QWidget *parent = nullptr);
    ~addRoiDialog();

    itemRoi* item() const { return mItemRoi; }



private slots:
    void on_toolButton_img1_clicked();
    void on_toolButton_img2_clicked();
    void on_toolButton_img3_clicked();
    void on_buttonBox_accepted();

    void on_buttonBox_rejected();

private:
    Ui::addRoiDialog *ui;
    itemRoi* mItemRoi;
    //int color, deploy;
    double size, conc, threeDlocation;
};

#endif // ADDROIDIALOG_H
