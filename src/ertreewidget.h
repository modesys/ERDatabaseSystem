#ifndef ERTREEWIDGET_H
#define ERTREEWIDGET_H

#include <QTreeWidget>

class QAction;
using ERTreeItem = QTreeWidgetItem;

class ERTreeWidget : public QTreeWidget
{
    Q_OBJECT
public:
    enum Type {
        NULLPTR,
        TABLE,
        BASE,
    };

ERTreeWidget(QWidget *parent = nullptr);
Type type(ERTreeItem *item) const;

Type type() const {
    return type(currentItem());
}

signals:
    void newTable();
    void newReferenceTable();
    void removeTable();
    void removeDatabase();
    void selectFrom();
    void editTable();


private:
    QAction *mActionNewTable;  // Creation of a new table
    QAction *mActionNewReferenceTable;  // Creation of a new reference table
    QAction *mActionRemoveTable; // Remove table
    QAction *mRemoveDatabase;  // Remove Database
    QAction *mSELECT_FROM; // implementation of the SQL commands on the GUI
    QAction *mActionEditTable; // Editing the table previous;y created

};


#endif // ERTREEWIDGET_H
