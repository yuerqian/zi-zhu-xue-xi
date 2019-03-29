#include "udpsever.h"
#include<QTimer>
#include<QDebug>
#include<QDateTime>

UdpSever::UdpSever(QWidget *parent) : QWidget(parent)
{
    _udpServer=new QUdpSocket;
    //绑定一个端口，udp不绑定端口也可以发送数据，但是接收不方便
    _udpServer->bind(10001);
    //绑定信号槽用来接收消息
    connect(_udpServer,SIGNAL(readyRead()),this,SLOT(slotReadyRead()));

    //发送消息，每几秒发送一次,设置定时器
    QTimer* time=new QTimer;
    time->setInterval(1000);
    time->start();//重置时间，开始倒计时
    connect(time,&QTimer::timeout,[&](){
        quint64 timetemp=QDateTime::currentMSecsSinceEpoch();//获取从1970年到现在的时间戳
        QString str=QString::number(timetemp);//整型转换为QString
        QByteArray strArray=str.toUtf8();
        #if 0//普通UDP
        _udpServer->writeDatagram(strArray,QHostAddress("127.0.0.1"),10002);//写数据,如果端口是1001（因为绑定了1001端口）就是发送到自己身上了
#endif
        #if 0//广播的方式发送
        _udpServer->writeDatagram(strArray,QHostAddress::Broadcast,10002);
#endif
        //多播发送方式,多播IP固定在224.0.0.1`225段
        _udpServer->writeDatagram(strArray,QHostAddress("224.0.0.131"),10002);


    });

}
void UdpSever::slotReadyRead()
{
    while(_udpServer->hasPendingDatagrams())//有数据时
    {
        //获取数据包大小
        qint64 dataSize=_udpServer->pendingDatagramSize();
        QByteArray buf(dataSize,0);//尽量不要是new申请内存，可以使用QByteArray申请内存
        //读取数据包
        _udpServer->readDatagram(buf.data(),buf.size());
        qDebug()<<buf;
    }

}
