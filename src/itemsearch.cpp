#include "itemsearch.h"

itemSearch::itemSearch(const QString &name, const QString &imageDescription,
                       const QString &fileType,
                       int color,
                       int idsearch,
                       const double size, const double threeDLocation, const double concavity,
                       const QByteArray &imagesData1,
                       const QByteArray &imagesData2)
{
    mName = name;
    mImageDescription = imageDescription;
    mFileType = fileType;
    mColor = color;
    mSearch = idsearch;
    mSize = size;
    m3DLocation = threeDLocation;
    mConcavity = concavity;
    mImagesData1 = imagesData1;
    mImagesData2 = imagesData2;
}
