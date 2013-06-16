#-------------------------------------------------
#
# Project created by QtCreator 2013-05-23T11:22:55
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = threadServer
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    mythread.cpp \
    myserver.cpp \
    servertools.cpp

HEADERS += \
    mythread.h \
    myserver.h \
    servertools.h

OTHER_FILES +=
