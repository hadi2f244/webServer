#include "tcpserver.h"

tcpserver::tcpserver(QObject *parent) :
    QObject(parent)
{
    server=new QTcpServer(this);
    connect(server,SIGNAL(newConnection()),this,SLOT(newConnection()));
    if(server->listen(QHostAddress::Any,1223)){
        qDebug()<<"Server is running ...";
    }
    else
    {
        qDebug()<<"ERROR!";
    }
}

void tcpserver::newConnection(){
    QTcpSocket *socket=server->nextPendingConnection();
    socket->write("hi client \r\n");
    socket->flush();//flush() send data to buffer!(?)
    socket->waitForBytesWritten(50000);
    socket->close();

}
