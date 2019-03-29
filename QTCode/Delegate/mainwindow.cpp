#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QVBoxLayout>
#include<algorithm>
#include<QtAlgorithms>
#include<QDebug>
#include<iterator>
#include<QLinkedList>
#include<QVector>

bool insensitiveLessThan(int a,int b)
{
    return a<b;//从小到大排序
    //return a>b;//从大到小排序
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget* widget=new QWidget(this);
    this->setCentralWidget(widget);

    Track t1("Song　1",200);
    Track t2("Song　2",150);
    Track t3("Song　3",120);
    Track t4("Song　4",210);
    list<<t1<<t2<<t3<<t4;
    TableWidget=new QTableWidget(list.count(),2);
    TableWidget->setItemDelegate(new TrackDelegate(1));//委托给另一个类进行管理
    TableWidget->setHorizontalHeaderLabels(QStringList()<<tr("Track")<<tr("Duration"));//设置列头
    //设置QTableWidget的每一项
    for(int row=0;row<list.count();row++)
    {
        Track track=list.at(row);
        QTableWidgetItem* item0=new QTableWidgetItem(track.title);
        TableWidget->setItem(row,0,item0);
        QTableWidgetItem* item1=new QTableWidgetItem(QString::number(track.duration));
        item1->setTextAlignment(Qt::AlignRight);
        TableWidget->setItem(row,1,item1);
    }
    QVBoxLayout* lay=new QVBoxLayout();
    lay->addWidget(TableWidget);
    widget->setLayout(lay);
#if 0
    QStringList list;
    list<<"Emma"<<"Karl"<<"James"<<"Mariette";
    QStringList::iterator i=qFind(list.begin(),list.end(),"Karl");
    QStringList::iterator j=qFind(list.begin(),list.end(),"Petra");
    if(j==list.end()&&i!=list.end())
        qDebug()<<*i;
#endif

#if 0
    QVector<int> vect(10);
    qFill(vect.begin(),vect.end(),999);
    QVector<int>::iterator i=vect.begin();
    while(i!=vect.end())
    {
        qDebug()<<*i;
    }
#endif

    #if 0
    QList<int> list1;
    list1<<1<<2<<3;
    QVector<int> vect(10);
    qCopy(list1.begin(),list1.end(),vect.begin()+8);//是迭代器操作，未赋值的部分用0补足
    QVector<int>::iterator i=vect.begin();
    while(i!=vect.end())
    {
        qDebug()<<*i;
        i++;
    }
    #endif

    QVector<int> vect;
    vect<<1<<4<<5<<5<<6<<8<<0<<3;
    qSort(vect.begin(),vect.end(),insensitiveLessThan);
    QVector<int>::iterator i=vect.begin();
    while(i!=vect.end())
    {
        qDebug()<<*i;
        i++;
    }


}

MainWindow::~MainWindow()
{
    delete ui;
}
