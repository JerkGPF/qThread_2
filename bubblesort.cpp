#include "bubblesort.h"

BubbleSort::BubbleSort(QObject *parent) : QObject(parent)
{

}



void BubbleSort::working(QVector<int> list)
{
    qDebug()<<"当前冒泡线程地址:"<<QThread::currentThread()<<endl;
    QElapsedTimer time;//计时
    time.start();
    int temp = 0;
    for(int i = 0;i<list.size();++i)
    {
        for(int j = 0; j<list.size()-i-1;++j)
        {
            if(list[j]>list[j+1])
            {
                temp = list[j];
                list[j] = list[j+1];
                list[j+1] = temp;
            }
        }
    }

    int milsec = time.elapsed();//计时结束
    qDebug()<<"冒泡排序用时:"<<milsec<<endl;
    emit finish(list);//将数据发送给主线程
}
