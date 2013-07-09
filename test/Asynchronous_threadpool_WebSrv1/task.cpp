#include "task.h"

Task::Task()
{
}


//now with this func we just recieve the request
//the question maybe coming is "Is there any problem with poeple requests and every client recieve the correct answer ?!

void Task::FileProcess(QString data)
{
    mData=new QString();
    *mData=data;
//    qDebug ()<<"it is ok";
}



void Task::run ()
{
    //time consumer
    qDebug ()<<"Task Start";
    QString rootPath; //This is the folder path that our files are there
    rootPath="/home/hadi/apps/hadi2f244/threadServer/htdocs";
    QStringList HttpParsed=HttpParser(*mData)["GET"];//for exam just recieve GET requests
    QString path=HttpParsed[0];
//    qDebug ()<<"path="<<path;
    QStringList argvs=HttpParsed;
    argvs.removeFirst ();//we don't need the file path in it!
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
            HTMLcode=phpRunner(path,argvs);
    }
    else if(fileType==".html" || fileType==".htm")
    {
            HTMLcode=file.readAll();
    }

    qDebug()<<"Task Done";
    emit result(HTMLcode);
}



QMap<QString,QStringList> Task::HttpParser(QString request){
    //Search the GET and POST and so on then import them to a map
    //in this func we have POSTlist & GETlist & ... that the first member of them is the path and other is argv(GET or POST variables)
    QMap<QString,QStringList> ParsedRequest;
    //but now we have to parsed the request to the lines because GET & POST request is in firstline




    //Knowing the GET or POST index
    if(request[0]=="G") //GET request //this is a safe GET reuest !!!
    {
        //parsing the sub directory path
        int Right,Left;
        Left=request.indexOf("/");
        qDebug ()<<"left ="<<Left;
        Right=request.indexOf(" ",Left);
        QStringList GETlist;
        GETlist.append (request.mid(Left,Right-Left));
        //qDebug()<<request.mid(Left,Right-Left);


        //we want to obtain the GET variables
        QRegExp GET("\\&\\w+=\\w+|\\?\\w+=\\w+\\&|\\&\\w+=\\w+");
        int count=request.count(GET);
        int from=0;
        int in=0;
        QStringList argvs;//this list contains the GET variable
        qDebug ()<<count;
        for(int i=0;i<count;i++)
        {
            in=GET.indexIn(request,from);
            argvs.append(GET.cap(0));
            from=in+argvs.value(i).size()-1;
        }

        //now we have have the GET vriables but we have to delete & and ?
        QRegExp ampReg,quesReg;
        ampReg.setPattern ("\\&");
        quesReg.setPattern ("\\?");
        for(int i=0;i<argvs.size ();i++)
        {
            QString temp=argvs[i];
            temp.replace (ampReg,"");
            temp.replace (quesReg,"");
            argvs[i]=temp;
        }
        GETlist+=argvs;
        ParsedRequest["GET"]= GETlist;
    }


    else if(request[0]=="P")
    {
        int Right,Left;
        Left=request.indexOf("/");
        Right=request.indexOf(" ",Left);
        QStringList POSTlist;
        POSTlist.append (request.mid(Left,Right-Left));
        ParsedRequest["POST"]=POSTlist;
        //qDebug()<<request.mid(Left,Right-Left);
    }
    else
    {
        qDebug()<<"The request isn't like a HTTP request";
    }    
    return ParsedRequest;
}




//This proccess php files
QString Task::phpRunner(QString path,QStringList argv)
{
    qDebug ()<<path;
    qDebug ()<<"path is:"<<path;
    QProcess *myProcess = new QProcess();
    QStringList args;
    args<<"-q"; //read the php-cgi manual
    args<<path;//we separated the path because we need to process the path
    args+=argv;
    myProcess->start("php-cgi",args);
    myProcess->waitForFinished();
    QString strout = myProcess->readAllStandardOutput();
    return strout; //this is the equal HTML codes
    delete myProcess;
    //Is php command running html?
}

