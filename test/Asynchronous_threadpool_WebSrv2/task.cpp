#include "task.h"
#include <iostream>

Task::Task()
{
}


//now with this func we just recieve the request
//the question maybe coming is "Is there any problem with poeple requests and every client recieve the correct answer ?!

void Task::FileProcess(QString data)
{
    mData=new QString();
    *mData=data;//mData was use in run func
}



void Task::run ()
{
    //time consumer
    qDebug ()<<"Task Start";
    QString rootPath; //This is the folder path that our files are there
    rootPath="/home/hadi/apps/hadi2f244/threadServer/htdocs";
//    qDebug ()<<"please enter the root path";

//    QTextStream qCin(stdin);
//    rootPath = qCin.readLine();
    bool POSTRequest=false; //we want to send post request to php runner directly

    QStringList HttpParsed=HttpParser(*mData); // we parsed the request string

    if(HttpParser(*mData)[0]=="GET")
    {

    }
    else if(HttpParser(*mData)[0]=="POST")
    {
        POSTRequest=true;
    }



    QString path=HttpParsed[1];
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
    }

    path=rootPath+path;

    QFile file(path);
    file.open(QIODevice::ReadOnly);
    if(file.exists())
        {
//            qDebug()<<"The file exists => "<<path;
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


    if(fileType==".php" | POSTRequest)
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



QStringList Task::HttpParser(QString request){
    //Search the GET and POST and so on then import them to a map
    //in this func we have POSTlist & GETlist & ... that the first member of them is the path and other is argv(GET or POST variables)
    QStringList ParsedRequest;//we will return this list


    //now we want to parse the request line by line
    int begin=0;
    QRegExp testReg("\r\n");
    QList<int> lines;
    lines<<0;
    while(1)
    {
        begin=testReg.indexIn (request,begin+1);
        if(begin==-1)
            break;
        lines<<begin;
    }
    QStringList strLines;
    for(int i=0;i<lines.size();i++) //top of i is lines.size()-1 because in POST method the last line is not empty
    {
        strLines<<request.mid(lines[i],lines[i+1]-lines[i]);
    }


    QString requestFLine=strLines[0];


    //Knowing the GET or POST index

     //GET request
    if(requestFLine[0]=='G') //I think this is safer way to reconize request method!
    {

        ParsedRequest<<"GET";
        //parsing the sub directory path
        int Right,Left;
        Left=requestFLine.indexOf("/");
        QRegExp pathReg("\\?|\\s");
        Right=pathReg.indexIn(requestFLine,Left+1);
        QStringList GETlist;
        GETlist.append (requestFLine.mid(Left,Right-Left));//append the path


        //we want to obtain the GET variables
        QRegExp GET("\\&\\w+=\\w+|\\?\\w+=\\w+\\&|\\&\\w+=\\w+");
        int count=requestFLine.count(GET);
        int from=0;
        int in=0;
        QStringList argvs;//this list contains the GET variable
        for(int i=0;i<count;i++)
        {
            in=GET.indexIn(requestFLine,from);
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
        ParsedRequest+=GETlist;
    }


    //POST request
    //POST request is denied !!! when improve that plz del this line!
    else if(requestFLine[0]=='P') //I think this is safer way to reconize request method!
    {
        ParsedRequest<<"POST";
        int Right,Left;
        Left=requestFLine.indexOf("/");
        QRegExp pathReg("\\s");
        Right=pathReg.indexIn(requestFLine,Left+1);
        QStringList POSTlist;
        POSTlist.append (requestFLine.mid(Left,Right-Left));

        QString requestLLine=strLines.last ();//last line obtains the post variables
        //now we obtain the post args
        QRegExp POST("\\&\\w+=\\w+|\\w+=\\w+\\&");
        int count=requestLLine.count(POST);
        int from=0;
        int in=0;
        QStringList argvs;//this list contains the GET variable
        for(int i=0;i<count;i++)
        {
            in=POST.indexIn(requestLLine,from);
            argvs.append(POST.cap(0));
            from=in+argvs.value(i).size()-1;
        }
        //now we have have the post vriables but we have to delete &
        QRegExp ampReg;
        ampReg.setPattern ("\\&");
        for(int i=0;i<argvs.size ();i++)
        {
            QString temp=argvs[i];
            temp.replace (ampReg,"");
//            qDebug ()<<temp;
            argvs[i]=temp;
        }
        POSTlist+=argvs;
        ParsedRequest+=POSTlist;
    }
    else
    {
//        qDebug()<<"The request isn't like a HTTP request";
    }
    return ParsedRequest;
}




//This proccess php files
QString Task::phpRunner(QString path,QStringList argv)
{
//    qDebug ()<<path;
//    qDebug ()<<"path is:"<<path;
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
}

