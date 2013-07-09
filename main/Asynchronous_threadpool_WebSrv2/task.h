#ifndef TASK_H
#define TASK_H

#include <QObject>
#include <QDebug>
#include <QRunnable>
#include <QMap>
#include <QFile>
#include <QDebug>
#include <QDir>
#include <QProcess>
#include <QStringList>

class Task :public QObject, public QRunnable
{
    Q_OBJECT
public:
    Task();
    QStringList HttpParser(QString request);
    void FileProcess(QString path);
    QString phpRunner(QString path,QStringList argv);
signals:
    void result(QString);
private:
    QString *mData;
protected:
    void run();
};

#endif // TASK_H
