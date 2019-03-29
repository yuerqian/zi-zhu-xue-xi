#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QBuffer>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_shareMemory(new QSharedMemory(this))
{
    ui->setupUi(this);
    m_shareMemory->setKey("share");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_loadFromMemory_clicked()
{
    if(!m_shareMemory->attach())
    {
        qDebug()<<"sharememory attach failed!";
        return;
    }
    //声明缓冲区
    QBuffer buffer;
    QDataStream in(&buffer);//读取缓冲区
    QImage image;
    m_shareMemory->lock();
    buffer.setData((char*)m_shareMemory->constData(),m_shareMemory->size());//将共享内存上的数据保存到缓冲区
    buffer.open(QBuffer::ReadOnly);
    in>>image;//
    m_shareMemory->unlock();
    ui->label->setPixmap(QPixmap::fromImage(image));
}
