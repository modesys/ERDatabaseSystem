#-------------------------------------------------
#
# Project created by QtCreator 2017-11-24T17:54:09
#
#-------------------------------------------------

QT       += core gui sql printsupport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = ERDatabaseSystem
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    ertreewidget.cpp \
    treewidget.cpp \
    finddialog.cpp \
    findform.cpp \
    findreplacedialog.cpp \
    findreplaceform.cpp \
    erpreferencesdialog.cpp \
    settings.cpp \
    newtabledialog.cpp \
    edittabledialog.cpp \
    buttoncolumndelegate.cpp \
    firstnestedtable.cpp \
    database.cpp \
    item.cpp \
    additemfirstnestedtabledialog.cpp \
    addroidialog.cpp \
    databaseroi.cpp \
    itemroi.cpp \
    roi.cpp

HEADERS  += mainwindow.h \
    ertreewidget.h \
    treewidget.h \
    finddialog.h \
    findform.h \
    findreplacedialog.h \
    findreplaceform.h \
    erpreferencesdialog.h \
    settings.h \
    define.h \
    newtabledialog.h \
    edittabledialog.h \
    buttoncolumndelegate.h \
    firstnestedtable.h \
    database.h \
    item.h \
    additemfirstnestedtabledialog.h \
    addroidialog.h \
    databaseroi.h \
    itemroi.h \
    roi.h

FORMS    += mainwindow.ui \
    findreplacedialog.ui \
    findreplaceform.ui \
    erpreferencesdialog.ui \
    newtabledialog.ui \
    edittabledialog.ui \
    firstnestedtable.ui \
    additemfirstnestedtabledialog.ui \
    addroidialog.ui \
    roi.ui

RESOURCES += \
    res.qrc

DISTFILES +=

QMAKE_CXXFLAGS += -std=gnu++14

