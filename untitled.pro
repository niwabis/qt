#-------------------------------------------------
#
# Project created by QtCreator 2017-04-20T19:17:02
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = untitled
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    minion.cpp \
    choosecard.cpp \
    tower.cpp

HEADERS  += mainwindow.h \
    minion.h \
    choosecard.h \
    tower.h

FORMS    += mainwindow.ui

RESOURCES += \
    res.qrc
