#ifndef SERVER_H
#define SERVER_H

#include <QTcpServer>
#include <QTcpSocket>
#include <QAbstractSocket>
#include "client.h"

class Server : public QTcpServer
{
    Q_OBJECT
public:
    explicit Server(QObject *parent = 0);
    void start();
signals:
private:
    int port;
public slots:
protected:
    void incomingConnection (int handle);
};

#endif // SERVER_H
