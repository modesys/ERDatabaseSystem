#ifndef ITEMSEARCH_H
#define ITEMSEARCH_H

#include <QObject>

class itemSearch
{
public:
    itemSearch(const QString &name, const QString &imageDescription,
               const QString &fileType,
               int color,
               int idsearch,
               const double size, const double threeDLocation, const double concavity,
               const QByteArray &imagesData1 = QByteArray(),
               const QByteArray &imagesData2 = QByteArray());

    QString name() const { return mName; }
    QString imageDescription() const { return mImageDescription; }
    QString fileType() const { return mFileType; }
    int color() const { return mColor; }
    int idsearch() const { return mSearch; }
    double size() const { return mSize; }
    double threeDLocation() const { return m3DLocation; }
    double concavity() const { return mConcavity; }
    QByteArray imagesData1() const { return mImagesData1; }
    QByteArray imagesData2() const { return mImagesData2; }

private:

    QString mName;
    QString mImageDescription;
    QString mFileType;
    int mColor;
    int mSearch;
    double mSize;
    double m3DLocation;
    double mConcavity;
    QByteArray mImagesData1;
    QByteArray mImagesData2;
};

#endif // ITEMSEARCH_H
