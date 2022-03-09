#ifndef MYTHREAD_H
#define MYTHREAD_H

#include <QObject>
#include <QThread>
#include <QVector>
class Generate : public QObject
{
    Q_OBJECT
public:
    explicit Generate(QObject *parent = nullptr);

    void working(int num);
signals:
    void sendData(QVector<int> data);

};

class BubbleSort : public QObject
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);

    void working(QVector<int> data);
signals:
    void finish(QVector<int> data);

};

class QuickSort : public QObject
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);

    void working(QVector<int> data);
private:
    void quickSort(QVector<int> &data,int l,int r);
signals:
    void finish(QVector<int> data);


};

#endif // MYTHREAD_H
