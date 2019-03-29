#include "jscontest.h"
#include<QMessageBox>
#include<QDebug>

jscontest::jscontest(QObject *parent) : QObject(parent)
{

}
void jscontest::OnMsg(QString Msg)//用来接收js发来的信息,其实是js直接调用槽函数
{
    qDebug()<<Msg;
    QMessageBox::about(NULL,"MESSAGE",Msg);
}
void jscontest::SendMsg(webview *web, const QString &msg)//向js发送消息，其实是调用js的函数
{
    //第一种方法，用信号，向js传递消息,js通过“注册名.sendMsgtoJS.connect(RecvMessage);”连接js函数function sendMessage(msg)，推荐
    emit sendMsgtoJS(msg);
    //第二种方法，直接调用HTML上的函数，只能在HTML上的函数使用，不推荐
    web->page()->runJavaScript(QString("RecvMessage2('%1');").arg(msg),[](const QVariant& v){//第二个参数是槽函数，用来接收js返回的值
        QMessageBox::about(NULL,"MESSAGE",v.toString());
    });//注意：参数要带分号'',并且该函数必须定义的在HTML文件中，在js中则提示找不到
}
