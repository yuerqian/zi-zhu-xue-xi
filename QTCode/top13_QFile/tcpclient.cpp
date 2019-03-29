#include "tcpclient.h"
#include<QHBoxLayout>
#include<QPushButton>

TcpClient::TcpClient(QWidget *parent) : QWidget(parent)
{
    m_tcpSocket=new QTcpSocket(this);
    m_tcpSocket->connectToHost("127.0.0.1",6665);//连接服务端,返回套接字

    m_lineEdit=new QLineEdit(this);
    QHBoxLayout* lay=new QHBoxLayout(this);
    lay->addWidget(m_lineEdit);
    QPushButton* button=new QPushButton("send");
    lay->addWidget(button);

    connect(button,SIGNAL(clicked(bool)),SLOT(slotButtonClick()));

}

void TcpClient::slotButtonClick()
{
    QString strText=m_lineEdit->text();//获取文本框内容，QString不适合传输，需要转化为
    if(strText.isEmpty())
        return;
    m_tcpSocket->write(strText.toUtf8());//往套接字写数据
    m_lineEdit->clear();//清空文本

}
