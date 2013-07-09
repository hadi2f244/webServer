#ifndef CLIENT_H
#define CLIENT_H

#include <QObject>
#include <QTcpSocket>
#include <QDebug>
#include <QThreadPool>
#include "task.h"

class Client : public QObject
{
    Q_OBJECT
public:
    explicit Client(QObject *parent = 0);
    void setSocket(int Descriptor);
signals:
    
public slots:
    void connected();
    void disconnected();
    void readyRead();
    void task(QString result);
private:
    QTcpSocket *socket;
    static int crashed_test;
};

#endif // CLIENT_H
