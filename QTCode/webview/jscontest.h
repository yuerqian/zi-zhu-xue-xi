#ifndef JSCONTEST_H
#define JSCONTEST_H

#include <QObject>
#include<webview.h>
//注意：与js交互的类，必须继承自QObject
class jscontest : public QObject
{
    Q_OBJECT
public:
    explicit jscontest(QObject *parent = 0);

public:
    void SendMsg(webview* webPage,const QString& msg);

signals:
    void sendMsgtoJS(QString Msg);//接收到js信号

public slots:
    void OnMsg(QString Msg);//用来接收js发来的信息
};

#endif // JSCONTEST_H
