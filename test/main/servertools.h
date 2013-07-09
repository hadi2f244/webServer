#ifndef SERVERTOOLS_H
#define SERVERTOOLS_H

#include <QObject>
#include <QMap>
#include <QFile>

class ServerTools : public QObject
{
    Q_OBJECT
public:
    explicit ServerTools(QObject *parent = 0);
    //QString rootPath; //This is the folder path that our files are there
    QMap<QString,QString> HttpParser(QString request);
    QString FileProcess(QString path);
    void php(QString path);
signals:

public slots:

private:

};

#endif // SERVERTOOLS_H
