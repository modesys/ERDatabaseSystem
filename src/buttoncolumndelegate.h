#ifndef IMAGEDELEGATE_H
#define IMAGEDELEGATE_H

#include <QAbstractItemDelegate>
#include <QSize>
#include <QPixmap>
#include <QPainter>
#include <QStylePainter>
#include <QStyledItemDelegate>
#include <QDebug>

class ImageDelegate : public QStyledItemDelegate
{
public:
    ImageDelegate(QObject * parent = 0);

    void paint(QPainter * painter, const QStyleOptionViewItem & option, const QModelIndex & index) const;
    QSize sizeHint(const QStyleOptionViewItem & option, const QModelIndex & index) const;
};

#endif // IMAGEDELEGATE_H
