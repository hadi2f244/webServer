#include "tcpsocket.h"

tcpsocket::tcpsocket(QObject *parent) :
    QObject(parent)
{

}
void tcpsocket::connect()
{
    tcp = new QTcpSocket(this);
    tcp->connectToHost("www.google.com",80);
    if(tcp->waitForConnected()){
        qDebug()<<"Connected";
        tcp->write("hi  \n\n\n\n");
        tcp->waitForReadyRead();
        qDebug()<<tcp->readAll();
        tcp->close();
    }
    else{
        qDebug()<<"Not Connected";
    }

}
