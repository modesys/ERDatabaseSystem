#include "insertvaluesxmlexcelcsv.h"

insertValuesXmlExcelCsv::insertValuesXmlExcelCsv(const QString &id, const QString &name,
                                                 const QString &image, const QString &roi)
{
    mId = id;
    mName = name;
    mImage = image;
    mRoi = roi;
}

void insertValuesXmlExcelCsv::setId(const QString &id)
{
    mId = id;
}

void insertValuesXmlExcelCsv::setName(const QString &name)
{
    mName = name;
}

void insertValuesXmlExcelCsv::setImage(const QString &image)
{
    mImage = image;
}

void insertValuesXmlExcelCsv::setRoi(const QString &roi)
{
    mRoi = roi;
}

QString insertValuesXmlExcelCsv::getId() const
{
    return mId;
}

QString insertValuesXmlExcelCsv::getName() const
{
    return mName;
}

QString insertValuesXmlExcelCsv::getImage() const
{
    return mImage;
}

QString insertValuesXmlExcelCsv::getRoi() const
{
    return mRoi;
}
