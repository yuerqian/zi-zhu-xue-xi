#include<QApplication>
#include<projectlistwidget.h>


int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    projectListWidget a;
    a.show();

    return app.exec();
}
