#include "mysignal.h"
#include<QDebug>

Mysignal::Mysignal(QObject *parent) : QObject(parent)
{
    qDebug()<<"aaaaa";

}

