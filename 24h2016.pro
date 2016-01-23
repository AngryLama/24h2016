#-------------------------------------------------
#
# Project created by QtCreator 2016-01-23T09:33:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 24h2016
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    laser.cpp \
    vue.cpp \
    jeu.cpp

HEADERS  += mainwindow.h \
    laser.h \
    vue.h \
    jeu.h

FORMS    += mainwindow.ui

RESOURCES += \
    application.qrc
