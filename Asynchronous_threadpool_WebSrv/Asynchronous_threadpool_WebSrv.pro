#-------------------------------------------------
#
# Project created by QtCreator 2013-06-20T12:21:09
#
#-------------------------------------------------

QT       += core
QT       += network
QT       -= gui

TARGET = Asynchronous_threadpool_WebSrv
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app


SOURCES += main.cpp \
    server.cpp \
    client.cpp \
    task.cpp

HEADERS += \
    server.h \
    client.h \
    task.h
