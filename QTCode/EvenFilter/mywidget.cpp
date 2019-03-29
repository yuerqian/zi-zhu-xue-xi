#include "mywidget.h"
#include "myapplication.h"
#include<QDebug>
static const QEvent::Type myevent=(QEvent::Type)(QEvent::registerEventType(QEvent::User + 100));
#define MSG_USERTES myevent

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{

    button=new QPushButton("button",this);
    connect(button,SIGNAL(clicked(bool)),this,SLOT(close()));
    //安装过滤器,相当于钩子函数
    button->installEventFilter(this);

}
bool MyWidget::eventFilter(QObject *watched, QEvent *event)
{
    //过滤鼠标的点击事件
    if(watched==button&&(event->type()==QEvent::MouseButtonPress
                         ||event->type()==QEvent::MouseButtonDblClick
                         ||event->type()==QEvent::MouseButtonRelease))
    {
        QEvent* m=new QEvent(QEvent::Type(MSG_USERTES));
        qApp->postEvent(this,m);
        return true;

    }
    return QWidget::eventFilter(watched,event);
}
bool MyWidget::event(QEvent *event)
{
    if(event->type()==MSG_USERTES)
    {
        qDebug()<<"QEvent::User=============";
    }
}
int main(int argc,char*argv[])
{
    MyApplication app(argc,argv);
    MyWidget w;
    w.show();
    //发送一个Event给MyWidget
    qDebug()<<"post start";
    QEvent* m=new QEvent(QEvent::Type(MSG_USERTES));
//    QEvent m(MSG_USERTES);
    app.postEvent(&w,m);//异步，postEvent可以发送给任何的Object对象,发送自定义user消息
    qDebug()<<"post end";
    qDebug()<<"send start";
    app.sendEvent(&w,m);//同步
    qDebug()<<"send end";
    return app.exec();
}
