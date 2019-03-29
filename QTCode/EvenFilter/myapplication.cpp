#include "myapplication.h"
#include<QDebug>

MyApplication::MyApplication(int argc,char*argv[]) : QApplication(argc,argv)
{

}
bool MyApplication::notify(QObject *watched, QEvent *event)
{
    //主窗口不在了也会进入notify，所以必须判断主窗口存在才能拿获取到主窗口（否则出现崩溃）
    if(this->topLevelWidgets().count()>0)
    {
        //获取主窗口
        QWidget* mainWidget=this->topLevelWidgets().at(0);//获取第一个主窗口，因为可能有很多个主窗口
        //拦截主窗口的鼠标点击消息
        if(watched==(QObject*)mainWidget&&(event->type()==QEvent::MouseButtonPress
                                 ||event->type()==QEvent::MouseButtonDblClick
                                 ||event->type()==QEvent::MouseButtonRelease))
        {
            qDebug()<<"mainWidget clicked";

        }

    }

    return QApplication::notify(watched,event);

}
