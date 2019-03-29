#ifndef MAINWINDOW_H
#define MAINWINDOW_H



#include <QMainWindow>
#include<webview.h>
#include<inspectable.h>
#include<jscontest.h>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;


    webview* m_webview;//HTML网页视图
    webview* m_webview2;//用来展示调试信息
    QWebChannel* m_webChannel;//创建和js交互的QWebChannel
    jscontest* m_jscontest;//与js交互的类

    //用来随程序的放大缩小来控制加载网页的大小
    void resizeEvent(QResizeEvent* size);

public slots:
    void slot_btnClick(){
       // m_webview2->setUrl(QString("http://127.0.0.1:7777"));
        m_webview2->reload();
    }
    void slot_btnClick2(){
        m_jscontest->SendMsg(m_webview,QString("农行!").toUtf8());
    }


};

#endif // MAINWINDOW_H
