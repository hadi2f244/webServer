#include "myserver.h"
#include <QDebug>
#include "mythread.h"

myServer::myServer(QObject *parent) :
    QTcpServer(parent)
{

}

void myServer::StartServer()
{
    if(!this->listen(QHostAddress::Any,1234))
    {
        qDebug() << "Could not running server";
    }
    else
    {
        qDebug() << "Listening...";
    }
}

void myServer::incomingConnection(int socketDescriptor)
{
    qDebug() << socketDescriptor << " Connecting... ";
    myThread *thread=new myThread(socketDescriptor,this);
    connect(thread,SIGNAL(finished()),thread,SLOT(deleteLater()));
    thread->start();
}


