#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QWidget>
//注意：需要定为到指定的文件夹路径
#include <QtWebEngineWidgets/QWebEngineView>

#include<QWebChannel>

//继承自QWebEngineView的类
class webview : public QWebEngineView
{
    Q_OBJECT
public:
    explicit webview(QWidget *parent = 0);

    webview* view;//跳转新的页面
     bool isview=false;//判断新页面是否创建，用来缩放新的页面

    //用来创建一个新的跳转页面
    virtual QWebEngineView* createWindow(QWebEnginePage::WebWindowType type);


signals:
    void newtabView(webview* view);

public slots:

};

#endif // WEBVIEW_H
