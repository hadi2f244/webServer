#ifndef MYSERVER_H
#define MYSERVER_H

#include <QTcpServer>

class myServer : public QTcpServer
{
    Q_OBJECT
public:
    explicit myServer(QObject *parent = 0);
    void StartServer();

signals:

public slots:

protected:
    void incomingConnection(int socketDescriptor);
};

#endif // MYSERVER_H
