#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
//#include<QLocalSocket>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    m_server=new QLocalServer(this);
    if(m_server->listen("fortune"));
    {
        fortunes << tr("You've been leading a dog's life. Stay off the furniture.")
                 << tr("You've got to think about tomorrow.")
                 << tr("You will be surprised by a loud noise.")
                 << tr("You will feel hungry again in another hour.")
                 << tr("You might have mail.")
                 << tr("You cannot kill time without injuring eternity.")
                 << tr("Computers are not intelligent. They only think they are.");
        connet(m_server,SIGNAL(newConnection()),this,SLOT(slotSendFutunes()));
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotSendFutunes()
{
//    // 从fortunes中随机取出一段字符串然后进行写入。
//    QByteArray block;
//    QDataStream out(&block, QIODevice::WriteOnly);
//    out.setVersion(QDataStream::Qt_4_0);
//    out << (quint16)0;
//    out << fortunes.at(qrand() % fortunes.size());
//    out.device()->seek(0);
//    out << (quint16)(block.size() - sizeof(quint16));

//    // nextPendingConnection()可以返回下一个挂起的连接作为一个连接的QLocalSocket对象。
//    QLocalSocket* clientConnection = m_server->nextPendingConnection();
//    connect(clientConnection, SIGNAL(disconnected()),clientConnection, SLOT(deleteLater()));

//    clientConnection->write(block);
//    clientConnection->flush();
//    clientConnection->disconnectFromServer();
}
