#ifndef UDPSEVER_H
#define UDPSEVER_H

#include <QWidget>
#include<QUdpSocket>

class UdpSever : public QWidget
{
    Q_OBJECT
public:
    explicit UdpSever(QWidget *parent = nullptr);
    QUdpSocket* _udpServer;

signals:

public slots:
    void slotReadyRead();
};

#endif // UDPSEVER_H
