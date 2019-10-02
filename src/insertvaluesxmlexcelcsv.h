#ifndef INSERTVALUESXMLEXCELCSV_H
#define INSERTVALUESXMLEXCELCSV_H

#include <QString>

class insertValuesXmlExcelCsv
{
public:
    insertValuesXmlExcelCsv(const QString &id = "", const QString &name = "",
                            const QString &image = "", const QString &roi = "");
    void setId(const QString &id);
    void setName(const QString &name);
    void setImage(const QString &image);
    void setRoi(const QString &roi);
    QString getId() const;
    QString getName() const;
    QString getImage() const;
    QString getRoi() const;

private:
    QString mId;
    QString mName;
    QString mImage;
    QString mRoi;
};

#endif // INSERTVALUESXMLEXCELCSV_H
