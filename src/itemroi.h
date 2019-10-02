#ifndef ITEMROI_H
#define ITEMROI_H
#include <QObject>
#include <QString>

class itemRoi
{
    //Q_OBJECT

public:
    itemRoi(const double size, const double threeDLocation, const double concavity,
            int color,
            int iddeployment,
            const QByteArray &imagesData1 = QByteArray(),
            const QByteArray &imagesData2 = QByteArray(),
            const QByteArray &imagesData3 = QByteArray());

    double size() const { return mSize; }
    double threeDLocation() const { return m3DLocation; }
    double concavity() const { return mConcavity; }
    int color() const { return mColor; }
    QByteArray imagesData1() const { return mImagesData1; }
    QByteArray imagesData2() const { return mImagesData2; }
    QByteArray imagesData3() const { return mImagesData3; }
    int iddeployment() const { return mIdDeployment; }

private:
    double mSize;
    double m3DLocation;
    double mConcavity;
    int mColor;
    QByteArray mImagesData1;
    QByteArray mImagesData2;
    QByteArray mImagesData3;
    int mIdDeployment;
};
#endif // ITEMROI_H
