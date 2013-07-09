#include "client.h"
#include <QHttpResponseHeader>
#include <QHttpRequestHeader>

Client::Client(QObject *parent) :
    QObject(parent)
{
    QThreadPool::globalInstance()->setMaxThreadCount(15);
}
int Client::crashed_test = 0;

void Client::setSocket (int Descriptor)
{
    socket=new QTcpSocket(this);

    connect(socket,SIGNAL(connected()),this,SLOT(connected()));
    connect(socket,SIGNAL(disconnected()),this,SLOT(disconnected()));
    connect(socket,SIGNAL(readyRead()),this,SLOT(readyRead()));

    socket->setSocketDescriptor(Descriptor);

    qDebug ()<<"Client connected";
}

void Client::connected ()
{
    qDebug ()<<"Client connected event";
}

void Client::disconnected()
{
    qDebug ()<<"Client disconnected";
}

void Client::readyRead ()
{
//    qDebug()<<socket->readAll ();
//    //time consumer - deadlock
//    Task *task=new Task();
//    task->setAutoDelete(true);
//    connect(task,SIGNAL(result(int)),SLOT(task(int)),Qt::QueuedConnection);
//    QThreadPool::globalInstance()->start (task);


//    QByteArray Data= socket->readAll();
//    QHttpResponseHeader *response=new QHttpResponseHeader();
//    QHttpRequestHeader *request=new QHttpRequestHeader();
//    //response->setStatusLine(404,"Not Found!");
//    //socket->write(response->toString().toAscii());
//    //delete response;
//    request=new QHttpRequestHeader();
//    qDebug ()<<Data;
//  socket->write(tool->FileProcess(Data).toAscii());
//  socket->waitForBytesWritten();
//  socket->flush();
    //the correct:
    QByteArray Data= socket->readAll();
    Task *task=new Task();
//    qDebug ()<<Data;
    task->FileProcess(Data);
    task->setAutoDelete(true);
    connect(task,SIGNAL(result(QString)),SLOT(task(QString)),Qt::QueuedConnection);//why doesn't have any this!
    QThreadPool::globalInstance()->start(task);
}

void Client::task (QString result)
{
    crashed_test+=1;
    qDebug ()<<crashed_test;
    socket->write(result.toAscii ());
    socket->flush();
    socket->close();
}
