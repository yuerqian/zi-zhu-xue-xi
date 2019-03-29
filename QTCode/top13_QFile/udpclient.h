#ifndef UDPCLIENT_H
#define UDPCLIENT_H

#include <QWidget>
#include<QUdpSocket>

class UdpClient : public QWidget
{
    Q_OBJECT
public:
    explicit UdpClient(QWidget *parent = nullptr);
    QUdpSocket* _udpClient;

signals:

public slots:
    void slotReadyRead();
};

#endif // UDPCLIENT_H
