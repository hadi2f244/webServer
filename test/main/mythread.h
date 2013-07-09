#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QThread>
#include <QTcpSocket>
#include <QDebug>
#include "servertools.h"

class myThread : public QThread
{
    Q_OBJECT
public:
    explicit myThread(int ID,QObject *parent = 0);
    ServerTools *tool;
    void run();
signals:
    void error(QTcpSocket::SocketError socketerror);
public slots:
    void readyRead();
    void disconnected();
private:
    QTcpSocket *socket;
    int socketDescriptor;
};

#endif // MYTHREAD_H
