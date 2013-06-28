#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QDebug>
#include <QRunnable>
#include <QMap>
#include <QFile>

class Task :public QObject, public QRunnable
{
    Q_OBJECT
public:
    Task();
    QMap<QString,QString> HttpParser(QString request);
    void FileProcess(QString path);
    QString phpRunner(QString path);
signals:
    void result(QString);
private:
    QString *mData;
protected:
    void run();
};

#endif // TASK_H
