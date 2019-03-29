
#include<QNetworkAccessManager>//网络访问管理器

#include<QCoreApplication>
#include<QNetworkReply>//应答
#include<QNetworkRequest>//请求
#include<QJsonObject>
#include<QJsonDocument>
#include<QDebug>
#include<QSettings>

int main(int argc,char* argv[])
{
    QCoreApplication app(argc,argv);
    QNetworkAccessManager* manager=new QNetworkAccessManager;//发送请求，和响应应答消息

#if 0
    //get请求
    QNetworkRequest req;
    //req.setUrl(QUrl("https://www.baidu.com"));//设置请求的网址
    //.cgi程序文件，是种公共网关接口脚步文件，即是http服务器与本地电脑或者其他服务器上程序进行“交谈”的种工具（软件）
    req.setUrl(QUrl("https://127.0.0.1/home/hm/TCR/Middle/a.out"));//运行服务器的c++程序

    manager->get(req);//发送请求并返回应答，通过槽函数监控返回
    QObject::connect(manager,&QNetworkAccessManager::finished,[](QNetworkReply* reply){//返回的应答
        if(reply->error()!=QNetworkReply::NoError)
        {
            qDebug()<<"Error:"<<reply->errorString();//打印错误信息
            return;
        }
        qDebug()<<"OK:"<<reply->readAll();//读取响应的数据

    });
#endif

#if 0
    QJsonObject obj;
    obj.insert("name",QString("momo"));
    obj.insert("sex",QString("男"));

    //post请求
    QNetworkRequest req;
    //req.setUrl(QUrl("http://www.baidu.com"));//设置请求的网址
    //.cgi程序文件，是种公共网关接口脚步文件，即是http服务器与本地电脑或者其他服务器上程序进行“交谈”的种工具（软件）
    req.setUrl(QUrl("http://192.168.43.134/home/hm/qtcode_practise/test-qt/test-qt.cgi"));//运行服务器的c++程序

    manager->post(req,QJsonDocument(obj).toJson());//发送请求并返回应答，通过槽函数监控返回
    QObject::connect(manager,&QNetworkAccessManager::finished,[](QNetworkReply* reply){//返回的应答
        if(reply->error()!=QNetworkReply::NoError)
        {
            qDebug()<<"Error:"<<reply->errorString();//打印错误信息
            return;
        }
        qDebug()<<"OK:"<<reply->readAll();//读取响应的数据

    });
#endif
//    QSettings* iniSetting=new QSettings("E:\\QTCode\\testttt\\MTransaction.ini",QSettings::IniFormat);
//    //1.设置ini文件的节
//    //    iniSetting->setValue("f/a","2");
////    iniSetting->beginGroup("f");
////    iniSetting->setValue("f/a", "2");
////    qDebug()<<iniSetting->value("info/color").toString();
//    iniSetting->setValue("info/color","fff");
////    iniSetting->endGroup();

//    QString str=QString("%1\\%2/%3").arg(QCoreApplication::applicationDirPath()).arg(QCoreApplication::applicationName()).arg("Qt5.5");
//     qDebug()<<str;
//     qDebug()<<QCoreApplication::organizationName();
//    QSettings* settings1=new QSettings(QSettings::IniFormat, QSettings::UserScope, QString("%1/%2/%3").arg(QCoreApplication::applicationDirPath()).arg(QCoreApplication::applicationName()).arg("Qt5.5"), "User");
//    settings1->setValue("/ff/aa","3");
//    settings1->setValue("fff/aaa","4");
//    qDebug()<<settings1->value("ff/aa").toString();

    QCoreApplication::setOrganizationName("MySoft");//会作为注册表的HKEY_CURRENT_USER\Software\MySoft
    QCoreApplication::setOrganizationDomain("mysoft.com");
    QCoreApplication::setApplicationName("Star Runner");//QSettings生成HKEY_CURRENT_USER\Software\MySoft\Star Runner路径
    QSettings settings;
    settings.setValue("aa","a");//分别作为名称和数据写到注册表（HKEY_CURRENT_USER\Software\MySoft\Star Runner）里面
    qDebug()<<"======"<<settings.fileName();//配置文件所在路径

    QSettings nativeSettings("HKEY_CURRENT_USER\\Software\\mynative\\qsettings",QSettings::NativeFormat);
    nativeSettings.setValue("test","te");
    qDebug()<<"tes=="<<nativeSettings.value("test").toString();
    qDebug()<<"======"<<nativeSettings.fileName();//配置文件所在路径

    return  app.exec();

}
