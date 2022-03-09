#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mythread.h"
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //1.创建子线程
    QThread* t1 = new QThread;
    QThread* t2 = new QThread;
    QThread* t3 = new QThread;
    //2.创建任务类的对象
    Generate* gen = new Generate;
    BubbleSort* bubble = new BubbleSort;
    QuickSort* quick = new QuickSort;
    //3.将任务对象移动到某个子线程中
    gen->moveToThread(t1);
    bubble->moveToThread(t2);
    quick->moveToThread(t3);

    //主线程发送个数给子线程
    connect(this,&MainWindow::starting,gen,&Generate::working);
    //2.启动子线程
    connect(ui->startButton,&QPushButton::clicked,this,[=]()
    {
        emit starting(10000);
        t1->start();
    });
    //接受排序数据
   connect(gen,&Generate::sendData,bubble,&BubbleSort::working);
   connect(gen,&Generate::sendData,quick,&QuickSort::working);

   //接受子线程发送的数据
    connect(gen,&Generate::sendData,[=](QVector<int> list)
    {
        t2->start();
        t3->start();
        for (int i =0;i<list.size();i++) {
            ui->randomList->addItem(QString::number(list.at(i)));

        }
    });
    connect(bubble,&BubbleSort::finish,[=](QVector<int> list)
    {
        for (int i =0;i<list.size();i++) {
            ui->bubbleList->addItem(QString::number(list.at(i)));

        }
    });
    connect(quick,&QuickSort::finish,[=](QVector<int> list)
    {
        for (int i =0;i<list.size();i++) {
            ui->quickList->addItem(QString::number(list.at(i)));
        }
    });
    //释放资源
    connect(this,&MainWindow::destroyed,this,[=]()
    {
        t1->quit();
        t1->wait();
        t1->deleteLater();

        t2->quit();
        t2->wait();
        t2->deleteLater();

        t3->quit();
        t3->wait();
        t3->deleteLater();

        gen->deleteLater();
        bubble->deleteLater();
        quick->deleteLater();
    });
}

MainWindow::~MainWindow()
{
    delete ui;
}

