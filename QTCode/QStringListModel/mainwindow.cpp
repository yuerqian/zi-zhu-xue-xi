
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QGridLayout>
#include<QPushButton>
#include<QInputDialog>
#include<QDebug>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model=new QStringListModel(this);
    QStringList data;
    data<<"Letter A"<<"Letter B"<<"Letter C";
    model->setStringList(data);

    listView=new QListView(this);
    listView->setModel(model);

    QPushButton* insertBtn=new QPushButton("Insert");
    QPushButton* delBtn=new QPushButton("Del");
    QPushButton* showBtn=new QPushButton("Show");
    connect(insertBtn,SIGNAL(clicked(bool)),this,SLOT(insertData()));
    connect(delBtn,SIGNAL(clicked(bool)),this,SLOT(delData()));
    connect(showBtn,SIGNAL(clicked(bool)),this,SLOT(showData()));

    QGridLayout* gLay=new QGridLayout(this);
    gLay->addWidget(listView,0,0,1,3);
    gLay->addWidget(insertBtn,1,0);
    gLay->addWidget(delBtn,1,1);
    gLay->addWidget(showBtn,1,2);


    ui->centralWidget->setLayout(gLay);

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::insertData()
{
    bool isOk;
    QString text=QInputDialog::getText(this,"Get Inset Data","Please Input New Data:",QLineEdit::Normal,"You are inseting new data",&isOk);
    if(isOk)
    {
        int curRow=listView->currentIndex().row()+1;//得到view当前行的索引内容的行数,+1表示往下一行插入数据
        qDebug()<<curRow;
        model->insertRows(curRow,1);//在第curRow行插入一行
        QModelIndex modelIndex=model->index(curRow);//得到model第row行的索引内容
        model->setData(modelIndex,text);//根据索引内容设置数据到model
        listView->setCurrentIndex(modelIndex);//设置索引内容为当前索引
        listView->edit(modelIndex);//设置当前项为可编辑状态
    }
}

void MainWindow::delData()
{
    if(model->rowCount()>=1)
    {
        model->removeRows(listView->currentIndex().row(),1);
    }
}

void MainWindow::showData()
{
    QStringList strList=model->stringList();
    QString str;
    foreach(QString data,strList)
    {
        str += data+"\n";
    }
    QMessageBox::information(this,"show data",str);
}
