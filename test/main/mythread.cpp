#include "mythread.h"
#include <QHttpResponseHeader>
#include <QHttpRequestHeader>


myThread::myThread(int ID,QObject *parent) :
    QThread(parent)
{
    this->socketDescriptor=ID;
}

void myThread::run()
{
    //thread starts here
        qDebug() << socketDescriptor << "Strting Thread";
        socket=new QTcpSocket();//Why this doesn't have any parent?!!!
        //qDebug()<<"Socket state1: "<<socket->state();
        if(!socket->setSocketDescriptor(this->socketDescriptor))
        {
            emit error(socket->error());
            return ;
        }
        else
        {
            connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()),Qt::DirectConnection);//Qt::DirectConnection is for that if a client want to connect doesn;t stop for her thread! directly connect to server then other works do.
            connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()),Qt::DirectConnection);

            qDebug() << socketDescriptor << "Client Connected";
            exec();
        }

}

void myThread::readyRead()
{
    QByteArray Data= socket->readAll();
    QString path=tool->HttpParser(Data)["GET"];
    QHttpResponseHeader *response=new QHttpResponseHeader();
    QHttpRequestHeader *request=new QHttpRequestHeader();
    response->setStatusLine(404,"Not Found!");
    socket->write(response->toString().toAscii());
    delete response;
    request=new QHttpRequestHeader();
    socket->write(tool->FileProcess(path).toAscii());
    //socket->waitForBytesWritten();
    socket->flush();
    socket->close();
}

void myThread::disconnected()
{
    qDebug() << socketDescriptor << "Disconnected";
    socket->deleteLater();
    exit(0);
}
