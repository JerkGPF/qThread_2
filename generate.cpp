#include "generate.h"
Generate::Generate(QObject *parent) : QObject(parent)
{

}



void Generate::working(int num)
{
    qDebug()<<"当前线程地址:"<<QThread::currentThread()<<endl;
    QVector<int> list;
    QElapsedTimer time;//计时
    time.start();
    for(int i = 0;i < num; ++i)
    {
        list.push_back(qrand()%10000);//生成10w以内随机数并放入list中
    }
    int milsec = time.elapsed();//计时结束
    qDebug()<<"生成"<<num<<"个随机数时间:"<<milsec<<endl;
    emit sendArray(list);//将数据发送给主线程
}
