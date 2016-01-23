#-------------------------------------------------
#
# Project created by QtCreator 2016-01-23T09:33:05
#
#-------------------------------------------------

QT       += core gui sql

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 24h2016
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    vue.cpp \
    dialognomniveau.cpp

HEADERS  += mainwindow.h \
    vue.h \
    dialognomniveau.h

FORMS    += mainwindow.ui \
    dialognomniveau.ui

RESOURCES += \
    application.qrc

DISTFILES += \
    myapp.rc

RC_FILE = myapp.rc
