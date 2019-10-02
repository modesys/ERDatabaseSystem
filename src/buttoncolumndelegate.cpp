#include "buttoncolumndelegate.h"

ImageDelegate::ImageDelegate(QObject * parent)
        : QStyledItemDelegate(parent)
{
}

QSize ImageDelegate::sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    return QSize(32,32);
    (void) option;
    (void) index;
}

void ImageDelegate::paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const
{
    qDebug() << (index.model()->headerData(index.column(), Qt::Horizontal).toString());
    QString colName = index.model()->headerData(index.column(), Qt::Horizontal).toString();

    if(colName == "images" || colName == "image_1" || colName == "image_2" || colName == "image_3")
    {
        QPixmap iconPix;
        if(!iconPix.loadFromData(index.model()->data(index).toByteArray())) {
        }

        iconPix = iconPix.scaledToHeight(32);

        painter->drawPixmap(option.rect.x(),option.rect.y(),iconPix);
    } else {
        QStyledItemDelegate::paint(painter, option, index);
    }
}
