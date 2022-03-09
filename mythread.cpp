#include "mythread.h"
#include <QElapsedTimer>
#include <QDebug>
Generate::Generate(QObject *parent) : QObject(parent)
{

}
void Generate::working(int num)
{
    qDebug()<<"当前线程地址："<<QThread::currentThread();
    QVector<int> list;
    QElapsedTimer timer;
    timer.start();
    for(int i = 0;i<num;i++)
    {
        list.push_back(qrand()%100000);
    }
    int milsec = timer.elapsed();
    qDebug()<<"时间："<<milsec<<"毫秒";
    emit sendData(list);
}

BubbleSort::BubbleSort(QObject *parent):QObject(parent)
{

}

void BubbleSort::working(QVector<int> data)
{
    qDebug()<<"当前线程地址："<<QThread::currentThread();
    QElapsedTimer timer;
    timer.start();
    int temp;
    for(int i = 0;i<data.size();i++)
    {
        for(int j = 0;j<data.size()-i-1;j++)
        {
            if(data[j]>data[j+1])
            {
                temp = data[j];
                data[j] = data[j+1];
                data[j+1] = temp;
            }
        }
    }
    int milsec = timer.elapsed();
    qDebug()<<"冒泡排序时间："<<milsec<<"毫秒";
    emit finish(data);
}


QuickSort::QuickSort(QObject *parent):QObject(parent)
{

}

void QuickSort::working(QVector<int> data)
{
    qDebug()<<"快速排序当前线程地址："<<QThread::currentThread();
    QElapsedTimer timer;
    timer.start();
    quickSort(data,0,data.size()-1);
    int milsec = timer.elapsed();
    qDebug()<<"快速排序时间："<<milsec<<"毫秒";
    emit finish(data);

}

void QuickSort::quickSort(QVector<int> &s, int l, int r)
{
    if (l < r)
    {
        int i = l, j = r;
        // 拿出第一个元素, 保存到x中,第一个位置成为一个坑
        int x = s[l];
        while (i < j)
        {
            // 从右向左找小于x的数
            while (i < j && s[j] >= x)
            {
                //左移, 直到遇到小于等于x的数
                j--;
            }
            if (i < j)
            {
                //将右侧找到的小于x的元素放入左侧坑中, 右侧出现一个坑
                //左侧元素索引后移
                s[i++] = s[j];
            }

            // 从左向右找大于等于x的数
            while (i < j && s[i] < x)
            {
                //右移, 直到遇到大于x的数
                i++;
            }
            if (i < j)
            {
                //将左侧找到的元素放入右侧坑中, 左侧出现一个坑
                //右侧元素索引向前移动
                s[j--] = s[i];
            }
        }
        //此时 i=j,将保存在x中的数填入坑中
        s[i] = x;
        quickSort(s, l, i - 1); // 递归调用
        quickSort(s, i + 1, r);
    }
}
