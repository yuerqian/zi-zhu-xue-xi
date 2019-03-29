#include "tcpserver.h"
#include<QHBoxLayout>
#include<QDebug>
#include<QNetworkInterface>//选择网络
#include "chooseinterface.h"
#include<QMessageBox>

TcpServer::TcpServer(QWidget *parent) : QWidget(parent)
{
    m_server=new QTcpServer;
    //第一种方法QNetworkInterface::allAddresses()，获取网卡ip
    chooseInterface dlg;//添加dialog，获取网卡上的所有IP
    dlg.exec();
    QMessageBox::information(NULL,"ip",dlg.strSelect);

    m_server->listen(QHostAddress(dlg.strSelect),6665);//QHostAddress::Any监听主机的任何一个ip端口，监听网卡上的所有IP,选择哪个ip作为接受数据
    connect(m_server,SIGNAL(newConnection()),this,SLOT(slotnewconnection()));//当有用户连接时响应
    m_textBrowser=new QTextBrowser;
    QHBoxLayout* lay=new QHBoxLayout(this);
    lay->addWidget(m_textBrowser);
}
//有用户连接时
void TcpServer::slotnewconnection()
{
    while(m_server->hasPendingConnections())//当有多个用户连接时，将每个用户的连接都取出来
    {
        m_socket=m_server->nextPendingConnection();//相当于网路编程的accept
        if(m_socket!=0)
        {
            qDebug()<<"aaaaa";
            connect(m_socket,SIGNAL(readyRead()),this,SLOT(slotReadyRead()));

        }else{
            qDebug()<<"m_socket==0";
        }

    }

}
//读取套接字里的数据
void TcpServer::slotReadyRead()
{
    while(m_socket->bytesAvailable()>0)//socket里有数据，就将数据读出来
    {
        QByteArray buf=m_socket->readAll();//接收所有的数据
        qDebug()<<buf;
        m_textBrowser->append(buf);
    }

}
