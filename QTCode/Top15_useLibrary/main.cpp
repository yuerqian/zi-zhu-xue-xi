#include<QCoreApplication>
#include"../top14_Library/top14_library.h"
//#include"../top16_lib/top16_lib.h"
#include<QString>
#include<stdio.h>
#include<string>

int main(int argc,char* argv[])
{
    QCoreApplication app(argc,argv);
    Top14_Library* ob=create();//ob=new Top14_Library();
    ob->Encrypt();
//    Top16_lib ol;
//    ol.encrypt();
    return app.exec();
}


