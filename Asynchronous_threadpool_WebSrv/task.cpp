#include "task.h"
#include <QDebug>
#include <QDir>
#include <QProcess>

Task::Task()
{
}

void Task::run ()
{
    //time consumer
    qDebug ()<<"Task Start";
    QString rootPath; //This is the folder path that our files are there
    rootPath="/home/hadi/apps/hadi2f244/threadServer/htdocs";
    QString path=HttpParser(*mData)["GET"];
    QString fileType,HTMLcode;
    if(path.contains(".",Qt::CaseSensitive))
    {
        //parsing the suffix
        int Left;
        Left=path.indexOf(".");
        fileType=path.mid(Left);
        qDebug()<<fileType;
    }

    path=rootPath+path;

    QFile file(path);
    file.open(QIODevice::ReadOnly);
    if(file.exists())
        {
            qDebug()<<"The file exists.";
        }
        else
        {
            qDebug()<<"The file not exists.";
            file.close();
            file.setFileName(rootPath+"/404error.html");
            file.open(QIODevice::ReadOnly);
            HTMLcode=file.readAll();
            file.close ();
        }

    if(fileType==".php")
    {
            HTMLcode=phpRunner(path);
    }
    else if(fileType==".html" || fileType==".htm")
    {
            HTMLcode=file.readAll();
    }

    qDebug()<<"Task Done";
    emit result(HTMLcode);
}

QMap<QString,QString> Task::HttpParser(QString request){
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

//now with this func we just recieve the request
//the question maybe coming is "Is there any problem with poeple requests and every client recieve the correct answer ?!

void Task::FileProcess(QString data)
{
    mData=new QString();
    *mData=data;
}

//This proccess php files
QString Task::phpRunner(QString path)
{
    QProcess *myProcess = new QProcess();
    QStringList args;
    args<<path;
    myProcess->start("php",args);
    myProcess->waitForFinished();
    QString strout = myProcess->readAllStandardOutput();
    return strout; //this is the equal HTML codes
    delete myProcess;
    //Is php command running html?
}

