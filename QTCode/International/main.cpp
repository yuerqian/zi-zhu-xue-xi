#include<QApplication>
#include<mainwindow.h>
#include<QTranslator>
#include<QMap>

int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    QTranslator translator;
    translator.load("E:\\QTCode\\International\\myapp.qm");
    app.installTranslator(&translator);
    MainWindow w;
    w.show();


    return app.exec();
}
