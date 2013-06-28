#include "server.h"

Server::Server(QObject *parent) :
    QTcpServer(parent)
{
}

void Server::start ()
{
    port=2424;
    if(listen(QHostAddress::Any,port))
    {
        qDebug()<<"Server started on port"<<port;
    }
    else
    {
        qDebug()<<"Server can't start";
    }
}

void Server::incomingConnection (int handle)
{
    Client *client=new Client(this);
    client->setSocket (handle);

}
