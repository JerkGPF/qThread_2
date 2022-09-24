#include "quicksort.h"
QuickSort::QuickSort(QObject *parent) : QObject(parent)
{

}



void QuickSort::working(QVector<int> list)
{
    qDebug()<<"当前快排线程地址:"<<QThread::currentThread()<<endl;
    QElapsedTimer time;//计时
    time.start();

    quickSort(list,0,list.size()-1);

    int milsec = time.elapsed();//计时结束
    qDebug()<<"快速排序用时:"<<milsec<<endl;
    emit finish(list);//将数据发送给主线程
}

void QuickSort::quickSort(QVector<int> &list, int l, int r)
{
    if(l < r)
    {
        int i = l,j =r;
        int x = list[l];
        while (i<j)
        {
            while(i < j && list[j] >= x)
            {
                j--;
            }
            if(i < j)
            {
                list[i++] = list[j];
            }
            while(i < j && list[i] < x)
            {
                i++;
            }
            if(i < j)
            {
                list[j--] = list [i];
            }
        }
        list[i] = x;
        quickSort(list,l,i - 1);
        quickSort(list,i + 1,r);
    }
}
