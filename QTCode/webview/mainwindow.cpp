#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QHBoxLayout>
#include<QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //HTML视图
    m_webview=new webview(this);
    qputenv("QTWEBENGINE_REMOTE_DEBUGGING", "7777");//注意：添加浏览器的F12调试信息（Inspectable）效果，必须在网页加载前构建好，通过http://127.0.0.1:7777打开调试网页
    //m_webview->page()->setUrl(QString("file:///C:/Users/Andy/Desktop/HTML5_test/homework.html"));//加载网页
    m_webview->page()->load(QString("https://www.baidu.com/"));//加载网页
    m_webview->show();

    //F12调试视图
    m_webview2=new webview(this);
    m_webview2->setUrl(QString("http://127.0.0.1:7777"));

    //创建QWebChannel,与js交互的通管道
    m_webChannel=new QWebChannel(this);
    //创建与js交互的类
    m_jscontest=new jscontest(this);
    //注册QWebChannel
    m_webChannel->registerObject(QStringLiteral("qtcontest"),m_jscontest);//注意：与js获取的名字必须一致，即js的channel.objects.qtcontest的qtcontest必须和qt注册的一致
    //设置当前HTML网页的通道-qt
    m_webview->page()->setWebChannel(m_webChannel);

    //添加布局
    QHBoxLayout* lay = new QHBoxLayout(this);
    QPushButton* btn=new QPushButton("reload");
    QPushButton* btn2=new QPushButton("tojs");
    connect(btn,SIGNAL(clicked(bool)),this,SLOT(slot_btnClick()));//刷新F12
    connect(btn2,SIGNAL(clicked(bool)),this,SLOT(slot_btnClick2()));
    lay->addWidget(btn);
    lay->addWidget(btn2);
    lay->addWidget(m_webview);
    //lay->addWidget(m_webview2);
    ui->centralWidget->setLayout(lay);
//    connect(m_webview,&webview::urlChanged,[&](const QUrl& url){
//        qDebug()<<url;
//        QUrl oldUrl=m_webview->url();
//        if(oldUrl!=url)
//            m_webview->load(url);
//    });

    // m_jscontest->SendMsg(m_webview,"hahahaha");
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::resizeEvent(QResizeEvent*)//自适应缩放
{
    m_webview->resize(this->size());
    //已经打开了一个tab类型的网页
    if(m_webview->isview)
        m_webview->view->resize(this->size());

}

