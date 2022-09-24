#ifndef QUICKSORT_H
#define QUICKSORT_H


#include <QObject>
#include <QVector>
#include <QDebug>
#include <QElapsedTimer>
#include <QThread>

class QuickSort : public QObject
{
    Q_OBJECT
public:
    explicit QuickSort(QObject *parent = nullptr);
    void working(QVector<int> list); //排序
signals:
    void finish(QVector<int> finishList);//发送排序完成的数据


private:
    void quickSort(QVector<int> &list,int l,int r);
};

#endif // QUICKSORT_H
