#ifndef TCPSOCKET_H
#define TCPSOCKET_H

#include <QObject>
#include <QDebug>
#include <QTcpSocket>

class tcpsocket : public QObject
{
    Q_OBJECT
public:
    QTcpSocket *tcp;
    explicit tcpsocket(QObject *parent = 0);
    void connect();
signals:
    
public slots:
    
};

#endif // TCPSOCKET_H
