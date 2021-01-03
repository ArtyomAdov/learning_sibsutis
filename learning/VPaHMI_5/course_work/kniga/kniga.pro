#-------------------------------------------------
#
# Project created by QtCreator 2020-12-20T16:37:35
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = kniga
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow1.cpp \
    database.cpp \
    dialogadd.cpp \
    dialogchangerecipe.cpp \
    helper.cpp

HEADERS  += mainwindow1.h \
    database.h \
    dialogadd.h \
    dialogchangerecipe.h \
    helper.h

FORMS    += mainwindow1.ui \
    dialogadd.ui \
    dialogchangerecipe.ui \
    helper.ui

RESOURCES += \
    splah.qrc
