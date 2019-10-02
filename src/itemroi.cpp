#include "itemroi.h"

itemRoi::itemRoi(const double size , const double threeDLocation, const double concavity,
                 int color, int iddeployment, const QByteArray &imagesData1, const QByteArray &imagesData2,
                 const QByteArray &imagesData3)
{
    mSize = size;
    //QString::(m3DLocation);
    //QString::number(mConcavity);
    m3DLocation = threeDLocation;
    mConcavity = concavity;
    mColor = color;
    mImagesData1 = imagesData1;
    mImagesData2 = imagesData2;
    mImagesData3 = imagesData3;

    mIdDeployment = iddeployment;
}
