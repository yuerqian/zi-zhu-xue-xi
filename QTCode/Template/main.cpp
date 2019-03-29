#include "mainwindow.h"
#include <QApplication>
#include<QDebug>
#include"templatetest.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    TemplateTest<int> test(8);
    qDebug()<<test.temp;
    int ff;
    ff=99;
    qDebug()<<test.function(5,ff);
    int aa=7;
    int b=99;
    qDebug()<<functiontest<int,double>(aa,b);

    return a.exec();
}
