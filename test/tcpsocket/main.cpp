#include <QCoreApplication>
#include "tcpsocket.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    tcpsocket tcp;
    tcp.connect();
    return a.exec();
}
