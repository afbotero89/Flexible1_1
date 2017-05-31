#-------------------------------------------------
#
# Project created by QtCreator 2017-03-17T15:52:29
#
#-------------------------------------------------

QT       += core gui
QT       += sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Flexible1_1
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    mainwindow_userselectedbed.cpp \
    mainwindowalarmsconfig.cpp

HEADERS  += mainwindow.h \
    mainwindow_userselectedbed.h \
    mainwindowalarmsconfig.h

FORMS    += mainwindow.ui \
    mainwindow_userselectedbed.ui \
    mainwindowalarmsconfig.ui

RESOURCES += \
    images.qrc

DISTFILES +=
