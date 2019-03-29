#include<QCoreApplication>//命令行形式
#include"mysignal.h"
#include"myslot.h"
#include<QObject>

int main(int argc,char* argv[])
{
    QCoreApplication app(argc,argv);
    Mysignal* sig=new Mysignal;//信号
    MySlot* slot=new MySlot;//槽
    QObject::connect(sig,SIGNAL(sig()),slot,SLOT(mySlot()));

    emit sig->sig();
//    emit sig.sig();
//    emit sig.sig();
//    emit sig.sig();
//    emit sig.sig();
//    emit sig.sig();
//    emit sig.sig();
//    emit sig.sig();



    return app.exec();
}
