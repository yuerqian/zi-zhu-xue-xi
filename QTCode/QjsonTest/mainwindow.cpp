
#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QJsonParseError>
#include<QJsonDocument>
#include<QJsonObject>
#include<QJsonArray>
#include<QJsonValue>
#include<QCryptographicHash>//hash表（哈希加密算法比如MD5）,用来加密，不可恢复
#include<QList>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //字符串json——QJsonDocument
    QString json("{"
                 "\"age\":36,"
                 "\"male\":true,"
                 "\"password\":\"9705f4a95416bb22b9017df875313d4c\","
                 "\"username\":\"xiaoxiao\","
                 "\"object\":{\"age2\":30,\"male\":true},"
                 "\"array\":[30,40,50]"
                 "}");

    //解析json,方法1（可以判断json数据类型，推荐）
    QJsonParseError error;
    QJsonDocument docjson=QJsonDocument::fromJson(json.toUtf8(),&error);//字符串json构造QJsonDocument
    if(error.error==QJsonParseError::NoError)//解析是否成功
    {
        if(docjson.isObject())
        {
            //QJsonDocument转换成QJsonObject
            QJsonObject object=docjson.object();
            //QJsonValue键值对数据
            if(object.value("password").isString())
            {
                qDebug()<<"对象的键的值："<<object.value("password").toString();//object取值
            }
            //QJsonObject数据
            if(object.value("object").isObject())
            {
                QJsonObject obj=object.value("object").toObject();
                qDebug()<<"对象的对象的键的值："<<obj.value("age2").toInt();
            }
            //QJsonArray数据
            if(object.value("array").isArray())
            {
                QJsonArray array=object.value("array").toArray();
                for(int i=0;i<array.size();i++)
                {
                    qDebug()<<"对象的数组："<<array.at(i).toInt();
                }
            }
        }
    }
    //解析json,方法2,QVariant（不可以判断数据类型，在知道是json数据情况下使用）
    if(error.error==QJsonParseError::NoError)//解析是否成功
    {
        if(docjson.isObject())
        {
            //原理：将 JSON 数据转换为 QVariant 对象，将 JSON 数组转换成 QVariantList 对象，将 JSON 对象转换成 QVariantMap 对象。
            //将 JSON 对象转换成 QVariantMap 对象
            QVariantMap result=docjson.toVariant().toMap();
            //键值
            qDebug()<<"对象的键的值:"<<result["password"].toString();
            //对象
            QVariantMap obj=result["object"].toMap();
            qDebug()<<"对象的对象的键的值："<<obj["age2"].toInt();
            //数组
            QVariantList list=result["array"].toList();
            foreach(QVariant temp,list)
            {
                qDebug()<<"对象的数组："<<temp.toInt();
            }

        }
    }
    else
    {
        qDebug()<<"解析失败："<<error.errorString().toUtf8().constData();
    }

    //生成json，方法一（QJsonObject方法，推荐）
    QJsonObject jsonObj;
    //json中的正常key-value（键值）
    jsonObj.insert("name","momo");
    QByteArray md5=QCryptographicHash::hash(QByteArray("xiaoren"),QCryptographicHash::Md5);//对密码字段进行加密，将字符串转转化为md5格式传输
    jsonObj.insert("password",QString(md5.toHex()));//toHex将数据转化为16进制再转变为字符串（比如char a=0x7f表示一个字节，toHex后就变为“7f"两个字节
    //json中的QJsonObject（对象）
    QJsonObject objChild;
    objChild.insert("companyName","meimei");
    objChild.insert("companyMail","88888@qq.com");
    jsonObj.insert("COMPANY",QJsonValue(objChild));//对象转换成键值，插入
    //json中的QJsonArray（数组）
    QJsonArray arrayChild;
    arrayChild.append("8");
    arrayChild.append("9");
    arrayChild.append("5");
    jsonObj.insert("LuckyNum",QJsonValue(arrayChild));//数组转换成键值，插入

    QJsonDocument docJson2;
    docJson2.setObject(jsonObj);
    //QJsonDocument——字符串json
    qDebug()<<"方法一生成结果："<<docJson2.toJson();//默认是自动缩进格式，结果："{\n    \"COMPANY\": {\n        \"companyMail\": \"88888@qq.com\",\n        \"companyName\": \"meimei\"\n    },\n    \"LuckyNum\": [\n        \"8\",\n        \"9\",\n        \"5\"\n    ],\n    \"name\": \"momo\",\n    \"password\": \"9705f4a95416bb22b9017df875313d4c\"\n}\n"
    qDebug()<<"方法一生成结果："<<docJson2.toJson(QJsonDocument::Compact);//（紧凑格式）没有换行的json格式，结果："{\"COMPANY\":{\"companyMail\":\"88888@qq.com\",\"companyName\":\"meimei\"},\"LuckyNum\":[\"8\",\"9\",\"5\"],\"name\":\"momo\",\"password\":\"9705f4a95416bb22b9017df875313d4c\"}"
    qDebug()<<"方法一生成结果："<<docJson2.toJson(QJsonDocument::Indented);//（自动缩进格式）自动换行的json格式，结果："{\n    \"COMPANY\": {\n        \"companyMail\": \"88888@qq.com\",\n        \"companyName\": \"meimei\"\n    },\n    \"LuckyNum\": [\n        \"8\",\n        \"9\",\n        \"5\"\n    ],\n    \"name\": \"momo\",\n    \"password\": \"9705f4a95416bb22b9017df875313d4c\"\n}\n"

    //生成json，方法二（QVariantList方法）
    QVariantMap docmap;
    docmap.insert("name","myname");//值
    docmap.insert("age",99);
    QVariantList docList;//数组
    docList<<55<<66<<88;
    QVariantMap map1;//对象
    map1.insert("companyName","haah");
    map1.insert("mail",888888888);
    docmap.insert("LuckNum",docList);//插入数组
    docmap.insert("COMPANY",map1);//插入对象

    QJsonDocument doc=QJsonDocument::fromVariant(docmap);
    if(!doc.isNull())
    {
        //结果："{\"COMPANY\":{\"companyName\":\"haah\",\"mail\":888888888},\"LuckNum\":[55,66,88],\"age\":99,\"name\":\"myname\"}""
        qDebug()<<"方法二生成结果："<<doc.toJson(QJsonDocument::Compact);
    }

}

MainWindow::~MainWindow()
{
    delete ui;
}
