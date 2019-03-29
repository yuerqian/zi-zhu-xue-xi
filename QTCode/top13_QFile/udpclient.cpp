#include "udpclient.h"
#include<QTimer>
#include<QDateTime>
UdpClient::UdpClient(QWidget *parent) : QWidget(parent)
{
    _udpClient=new QUdpSocket;
    //绑定一个端口，udp不绑定端口也可以发送数据，但是接收不方便
    _udpClient->bind(QHostAddress::AnyIPv4,10002);
    //加入到多播里
    _udpClient->joinMulticastGroup(QHostAddress("224.0.0.131"));

    //绑定信号槽用来接收消息
    connect(_udpClient,SIGNAL(readyRead()),this,SLOT(slotReadyRead()));

    //每几秒发送一次,设置定时器
    QTimer* time=new QTimer;
    time->setInterval(1000);
    time->start();//重置时间，开始倒计时
    connect(time,&QTimer::timeout,[&](){
        quint64 timetemp=QDateTime::currentMSecsSinceEpoch();//获取从1970年到现在的时间戳
        QString str=QString::number(timetemp);//整型转换为QString
        QByteArray strArray=str.toUtf8();
        _udpClient->writeDatagram(strArray,QHostAddress("127.0.0.1"),10001);//写数据发送,如果端口是1001（因为绑定了1001端口）就是发送到自己身上了
    });

}

void UdpClient::slotReadyRead()
{
    while(_udpClient->hasPendingDatagrams())
    {
        //获取数据包大小
        qint64 dataSize=_udpClient->pendingDatagramSize();
        QByteArray buf(dataSize,0);//尽量不要是new申请内存，可以使用QByteArray申请内存
        //读取数据包
        _udpClient->readDatagram(buf.data(),buf.size());
        qDebug()<<"UdpClient receive:"<<buf;
    }


}
