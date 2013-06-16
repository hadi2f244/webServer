#include "servertools.h"
#include <QDebug>
#include <QDir>
#include <QProcess>

ServerTools::ServerTools(QObject *parent) :
    QObject(parent)
{
}

QMap<QString,QString> ServerTools::HttpParser(QString request){
    //Search the GET and POST and so on then import them to a map
    QMap<QString,QString> ParsedRequest;
    //Knowing the GET or POST index
    if(request.contains("GET",Qt::CaseSensitive))
    {
        //parsing the sub directory path
        int Right,Left;
        Left=request.indexOf("/");
        Right=request.indexOf(" ",Left);
        ParsedRequest["GET"]=request.mid(Left,Right-Left);
        //qDebug()<<request.mid(Left,Right-Left);
    }
    else if(request.contains("POST",Qt::CaseSensitive))
    {
        int Right,Left;
        Left=request.indexOf("/");
        Right=request.indexOf(" ",Left);
        ParsedRequest["POST"]=request.mid(Left,Right-Left);
        //qDebug()<<request.mid(Left,Right-Left);
    }
    else
    {
        qDebug()<<"The request isn't like a HTTP request";
    }
    return ParsedRequest;
}

QString ServerTools::FileProcess(QString path)
{
    QString rootPath; //This is the folder path that our files are there
    rootPath="/home/hadi/apps/hadi2f244/threadServer/htdocs";
    path=rootPath+path;
    php(path);
    QFile file(path);
    file.open(QIODevice::ReadOnly);
    if(file.exists())
        qDebug()<<"The file exists.";
    else
        qDebug()<<"The file not exists.";
    return file.readAll();

}
void ServerTools::php(QString path)
{
    QProcess *process=new QProcess;
    QStringList args;
    args<<path;
    process->start("php",args);
    qDebug()<<process->readAll();
    delete process;
}

