#include "myslot.h"
#include<QDebug>
#include"mysignal.h"

MySlot::MySlot(QObject *parent) : QObject(parent)
{

}
void MySlot::mySlot()
{
    qDebug()<<"MySlot::mySlot is called";
    qDebug()<<i++;
    Mysignal sig;
    QObject::connect(&sig,SIGNAL(sig()),this,SLOT(mySlot2()));

}
void MySlot::mySlot2()
{
    qDebug()<<"MySlot::mySlot2 is called";
    qDebug()<<i2++;


}
