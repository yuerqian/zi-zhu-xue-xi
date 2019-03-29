#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QFileDialog>
#include<QBuffer>

const char* KEY_SHARE_MEMOTY="share";

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_ShareMemory(new QSharedMemory(KEY_SHARE_MEMOTY,this))
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadImage_clicked()
{
    if(m_ShareMemory->isAttached())
    {
        if(!m_ShareMemory->detach())
        {
            qDebug()<<"detach sharememory fail!";
        }
    }

    QString fileName=QFileDialog::getOpenFileName(this,"获取图片",".","Images (*.png *.xpm *.jpg)");
    QImage image;
    if(!image.load(fileName))
    {
        qDebug()<<"image load fail";
        return;
    }

    QBuffer bufer;
    bufer.open(QBuffer::ReadWrite);
    QDataStream out(&bufer);
    out<<image;
    int size=bufer.size();

    if(!m_ShareMemory->create(size))
    {
        qDebug()<<m_ShareMemory->errorString()<<"\n Unable Create ShareMemoty!";
        return;
    }
    m_ShareMemory->lock();
    char* to=(char*)m_ShareMemory->data();//返回指向共享内存的指针
    const char* from=bufer.data().data();
    memcpy(to,from,qMin(m_ShareMemory->size(),size));//
    m_ShareMemory->unlock();



}
