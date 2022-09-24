#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <QElapsedTimer>
#include <QThread>
class Generate : public QObject
{
    Q_OBJECT
public:
    explicit Generate(QObject *parent = nullptr);

    void working(int num); //生成随机数
signals:
    void sendArray(QVector<int> num);//自定义信号发送数据

};

#endif // MYTHREAD_H
