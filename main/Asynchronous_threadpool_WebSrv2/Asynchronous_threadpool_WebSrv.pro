#-------------------------------------------------
# Hadi2f244
# This is a simple HTTP server with:
#     Multithreaded with threadpool
#     HTTP parser
#     Match with GET & POST request
#-------------------------------------------------
# Will becoming:
#     1-Match with other HTTP request
#     2-Having a complete HTTP parser & Creating a new class for that
#     3-Can match with coockies & seasions
#     4-Asp (if possible!!!)
#     5-optimize the multithreading
#     6-configure file
#     7-HTTP Response
#
#-------------------------------------------------
# About codes:
#     main.cpp   : Just run server!
#     server.cpp : Manage the server
#     client.cpp : Manage the clients and threadpool class
#     task.cpp   : Manage HTTP and run the code and ...
#
# You can change the rootpath in task.cpp
# You can change the port in server.cpp
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
