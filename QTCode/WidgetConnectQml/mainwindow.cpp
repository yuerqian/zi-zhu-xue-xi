#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QtQuickWidgets/QQuickWidget>
#include<QHBoxLayout>
#include<QPushButton>
#include<QQuickView>
#include<QQuickItem>
#include<QQmlContext>
#include"person.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget* widget=new QWidget();
    takeCentralWidget();
    this->setCentralWidget(widget);
# if 1
    //方法一：QQuickWidget方法
#if 0
    QQuickWidget *pWidget = new QQuickWidget();
    pWidget->setResizeMode(QQuickWidget::SizeRootObjectToView);
    pWidget->setSource(QUrl("qrc:/qml/MainForm.ui.qml"));
#endif
    //方法二：QQuickView方法，推荐
    QQuickView *view = new QQuickView();
    view->setResizeMode(QQuickView::SizeViewToRootObject);
    Person* person=new Person();
    //嵌入属性
    view->rootContext()->setContextProperty("person",person);
    // 使用 QML 类型系统注册
    qmlRegisterType<Person>("People.com", 1, 0, "Person22");
    qmlRegisterType<IDCard>("People.com", 1, 0, "IDCard22");
    view->setSource(QUrl("qrc:/qml/MainForm.ui.qml"));
    //Qwindow转换为QWidget
    QWidget* pWidget=QWidget::createWindowContainer(view, this);

    QHBoxLayout* lay=new QHBoxLayout();
    QPushButton* btn=new QPushButton("发送信号");
    lay->addWidget(pWidget);
    lay->addWidget(btn);

    //widget与qml的信号交互
#if 0
    QObject* pRoot=(QObject*)pWidget->rootObject();//转换跟节点为QObject
#endif
    QObject* pRoot=(QObject*)view->rootObject();//转换跟节点为QObject
    QQuickItem* item=view->rootObject();
//    item->setProperty("color","red");
    if(pRoot!=NULL)
    {
//        QObject* child=pRoot->findChild<QObject*>("text");//注意需要制定类的模板类型为<QObject*>
//        child->setProperty("color","red");
        connect(btn,SIGNAL(clicked(bool)),pRoot,SIGNAL(widgetsignal()));//发送信号到qml,信号发送信号
        connect(pRoot,SIGNAL(qmlsignal()),this,SLOT(slotRecvQmlMessage()));//接收qml信号
    }


    widget->setLayout(lay);

#endif

    //QQmlComponent方法





}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotRecvQmlMessage()
{
    qDebug()<<"widget has received Qml Message";
}
