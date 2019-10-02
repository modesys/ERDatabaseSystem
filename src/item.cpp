#include "item.h"

item::item(const QString &roi, const QString &name, const QString &image,
           const QByteArray &imagesData)
{
    mRoi = roi;
    mName = name;
    mImage = image;
    mImagesData = imagesData;

}

