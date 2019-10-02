#ifndef ITEM_H
#define ITEM_H
#include <QString>

class item  // AbstractData
{
public:
    item(const QString &roi = "", const QString &name = "", const QString &image = "",
         const QByteArray &imagesData = QByteArray());

    QString roi() const { return mRoi; }
    QString name() const { return mName; }
    QString image() const { return mImage; }
    QByteArray imagesData() const { return mImagesData; }

private:
    QString mRoi;
    QString mName;
    QString mImage;
    QByteArray mImagesData;
};

#endif // ITEM_H
