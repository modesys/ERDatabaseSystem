#include "ertreewidget.h"
#include <QAction>
#include <QMouseEvent>

ERTreeWidget::ERTreeWidget(QWidget *parent)
      :QTreeWidget(parent)
{
    // initialization of the table
    mActionNewTable = new QAction(QIcon(":table"), "New Table", this);
    mActionNewReferenceTable = new QAction(QIcon(":table"), "New Reference Table", this);
    mActionRemoveTable = new QAction(QIcon(":"), "Remove Table", this);
    mRemoveDatabase = new QAction(QIcon(":"), "Remove Database", this);
    mSELECT_FROM = new QAction(QIcon(":"), "SELECT * FROM", this);
    mActionEditTable = new QAction(QIcon(":"), "Edit Table", this);
    //auto separator = new QAction(this);
    //separator->setSeparator(true);

    addActions({ mActionNewTable, mActionNewReferenceTable, mActionRemoveTable, mRemoveDatabase, mSELECT_FROM, mActionEditTable });

    connect(mActionNewTable, &QAction::triggered, [&]() {
        emit newTable();
    });

    connect(mActionNewReferenceTable, &QAction::triggered, [&]() {
        emit newReferenceTable();
    });

    connect(mActionRemoveTable, &QAction::triggered, [&]() {
        emit removeTable();
    });

    connect(mRemoveDatabase, &QAction::triggered, [&]() {
       emit removeDatabase();
    });

    connect(mSELECT_FROM, &QAction::triggered, [&]() {
        emit selectFrom();
    });

    connect(mActionEditTable, &QAction::triggered, [&]() {
        emit editTable();
    });
}

ERTreeWidget::Type ERTreeWidget::ERTreeWidget::type(ERTreeItem *item) const {
    if (item == nullptr) {
        return NULLPTR;
    }
    auto padre = item->parent();
    if (padre == nullptr) {
        return BASE;
    }
    return TABLE;
}

