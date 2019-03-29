#include "mywidget.h"
#include<QApplication>

int main(int argv,char* argc[])
{
    QApplication app(argv,argc);
    mywidget w;
    w.show();

    return app.exec();

}
