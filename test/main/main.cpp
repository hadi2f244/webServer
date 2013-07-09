#include <QtCore/QCoreApplication>
#include "myserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    myServer server;
    server.StartServer();
    return a.exec();
}
