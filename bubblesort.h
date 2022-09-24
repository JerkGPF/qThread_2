#ifndef BUBBLESORT_H
#define BUBBLESORT_H

#include <QObject>
#include <QVector>
#include <QDebug>
#include <QElapsedTimer>
#include <QThread>
class BubbleSort : public QObject
{
    Q_OBJECT
public:
    explicit BubbleSort(QObject *parent = nullptr);
    void working(QVector<int> list); //进行排序
signals:
    void finish(QVector<int> finishList);//发送排序完成的数据


};

#endif // BUBBLESORT_H
