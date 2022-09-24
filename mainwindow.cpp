#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //1.创建子线程对象
    QThread* t1 = new QThread;
    QThread* t2 = new QThread;
    QThread* t3 = new QThread;
    //2.创建任务类对象
    Generate* gen = new Generate;
    BubbleSort* bubble = new BubbleSort;
    QuickSort* quick = new QuickSort;
    //3.讲任务对象移动到某个子线程中
    gen->moveToThread(t1);
    bubble->moveToThread(t2);
    quick->moveToThread(t3);
    //4.启动子线程
    connect(ui->start,&QPushButton::clicked,[=]()
    {
       //4.1发送信号告知子线程需要多少个数据
        emit starting(10000);
        //4.2启动子线程
        t1->start();
    });
    //4.3子线程接收数据并启动工作函数
    connect(this,&MainWindow::starting,gen,&Generate::working);
    //5.主线程接收数据
    connect(gen,&Generate::sendArray,this,[=](QVector<int> list)
    {
        //5.1随机数生成完毕，调用子线程进行排序
        for (int i = 0;i < list.size();++i) {
            ui->random->addItem(QString::number(list.at(i)));
        }
        //5.2启动排序线程
        t2->start();
        t3->start();
    });
    //5.3随机数线程发送数据给排序线程
    connect(gen,&Generate::sendArray,bubble,&BubbleSort::working);
    connect(gen,&Generate::sendArray,quick,&QuickSort::working);
    //6.排序完成，主线程接收数据
    connect(bubble,&BubbleSort::finish,this,[=](QVector<int> list)
    {
        //6.1冒泡排序完成
        for (int i = 0;i < list.size();++i) {
            ui->boubbleSort->addItem(QString::number(list.at(i)));
        }

    });
    connect(quick,&QuickSort::finish,this,[=](QVector<int> list)
    {
        //6.2快速排序完成
        for (int i = 0;i < list.size();++i) {
            ui->quickSort->addItem(QString::number(list.at(i)));
        }
    });

    //7.释放资源
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

