#include "postandgetmessage.h"
#include<QApplication>
#include<QDebug>
#include<QMessageBox>




PostAndGetMessage::PostAndGetMessage(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* lay=new QVBoxLayout(this);
    label=new QLabel("nnnn",this);
    lay->addWidget(label);
    lay->addWidget(button=new QPushButton("test",this));
    QObject::connect(button, SIGNAL(clicked(bool)), this, SLOT(on_pushButton_clicked()));
    lay->addWidget(edit=new QLineEdit());
    m_accessManager = new QNetworkAccessManager(this);
    QObject::connect(m_accessManager, SIGNAL(finished(QNetworkReply*)), this, SLOT(finishedSlot(QNetworkReply*)));

}
PostAndGetMessage::~PostAndGetMessage()
{
    delete m_accessManager;
}
void PostAndGetMessage::finishedSlot(QNetworkReply *reply)
{
    if (reply->error() == QNetworkReply::NoError)
         {
             QByteArray bytes = reply->readAll();
             qDebug()<<bytes;
             QString string = QString::fromUtf8(bytes);
            // label->setText(string.toUtf8());
             QMessageBox::about(this,"提示",string.toUtf8());
             edit->setText(string.toUtf8());
             //ui->textBrowser->setText(string.toUtf8());

             if(times==0)
             {
                 times=1;
                 on_pushButton_clicked();

             }
         }
         else
         {
             qDebug()<<"handle errors here";
             QVariant statusCodeV = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute);
             //statusCodeV是HTTP服务器的相应码，reply->error()是Qt定义的错误码，可以参考QT的文档
             qDebug( "found error ....code: %d %d\n", statusCodeV.toInt(), (int)reply->error());
             qDebug(qPrintable(reply->errorString()));
         }
         reply->deleteLater();

}
void PostAndGetMessage::on_pushButton_clicked()
{
//POST

    if(times==1)
    {
        times=2;
        request.setUrl(QUrl("http://192.168.10.210:8080/idquery/TuxSingleCheckAction.do?op=select"));
    }
    else if(times==0)
    {
       request.setUrl(QUrl("http://192.168.10.210:8080/idquery/LoginAction.do?op=login"));
    }

//    request.setHeader(QNetworkRequest::ContentTypeHeader,"application/x-www-form-urlencoded");
//    request.setRawHeader("Accept","text/html, application/xhtml+xml, */*");
//    request.setRawHeader("Referer","http://localhost:8888/login");
//    request.setRawHeader("Accept-Language","zh-CN");
//    request.setRawHeader("X-Requested-With","XMLHttpRequest");
//    request.setRawHeader("User-Agent","Mozilla/5.0 (compatible; MSIE 9.0; Windows NT 6.1; WOW64; Trident/5.0)");
//    request.setRawHeader("Content-Type","application/x-www-form-urlencoded");
//    request.setRawHeader("Accept-Encoding","gzip,deflate");
//    request.setRawHeader("Host","localhost:8888");
//    request.setRawHeader("Content-Length","18");
    request.setRawHeader("Connection","Keep-Alive");
    request.setRawHeader("Cache-Control","no-cache");

    QByteArray postData;
    if(times==1)
    {
        times=2;
        postData.append("BranchCode=11005293&BizChType=01&&ID1=45082119930216081X&Name1=莫荣乾");
    }
    else if(times==0)
    {
        postData.append("BranchCode=11005293&BizChType=01");
    }


    QNetworkReply* reply = m_accessManager->post(request,postData);
}
int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
    PostAndGetMessage w;
    w.show();

    return app.exec();
}
