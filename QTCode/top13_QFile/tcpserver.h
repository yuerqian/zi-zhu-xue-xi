#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QWidget>
#include<QTcpServer>
#include<QTcpSocket>
#include<QTextBrowser>

class TcpServer : public QWidget
{
    Q_OBJECT
public:
    explicit TcpServer(QWidget *parent = nullptr);
    QTcpServer* m_server;//服务端
    QTcpSocket* m_socket;//套接字
    QTextBrowser* m_textBrowser;//只读的多行文本框

signals:

public slots:
    void slotnewconnection();//响应到来的连接
    void slotReadyRead();//响应socket
};

#endif // TCPSERVER_H
