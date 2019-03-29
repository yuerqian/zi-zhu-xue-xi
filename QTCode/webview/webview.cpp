#include "webview.h"

webview::webview(QWidget *parent) : QWebEngineView(parent)
{

}

QWebEngineView* webview::createWindow(QWebEnginePage::WebWindowType type)
{
    //Q_UNUSED(type);//用来避免未引用变量引起的警告
    //打开一个tab类型的网页
    if(type==QWebEnginePage::WebBrowserTab)
    {
        qDebug()<<"fadfjjlsldjjfa:"+this->url().toString()<<"===="<<type;
        //1.new webview(this)会覆盖在当前QWebEngineView上，但是原来的view还存在只是被覆盖了；
        //2.new webview打开一个新窗口显示
        view = new webview(this);//不断地创建新的view是否会造成内存泄漏，不清楚
        view->resize(this->size());
        view->show();//必须要show出来
        isview=true;
        return view;//直接返回return this;不可以覆盖跳转页面，不知道为什么
    }
    return this;
}

