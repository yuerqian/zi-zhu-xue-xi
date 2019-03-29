#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QGraphicsScene>
#include<QGraphicsView>
#include<QHBoxLayout>
#include<QContextMenuEvent>
#include<QDebug>
#include<QPushButton>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    oldWidget=centralWidget();
    widget=new QWidget();


    QHBoxLayout* lay=new QHBoxLayout();
    QGraphicsScene* sence=new QGraphicsScene();
    QGraphicsView* view=new QGraphicsView();
    view->setScene(sence);
    sence->addLine(0,0,100,100);

    QPushButton* btn=new QPushButton("nihao");
    connect(btn,&QPushButton::clicked,this,&MainWindow::slotbtnclick);
    lay->addWidget(view);
    lay->addWidget(btn);
    widget->setLayout(lay);
    takeCentralWidget();//拿走已经存在的CentralWidget()，否则下次setCentralWidget时容易出现崩溃
    this->setCentralWidget(widget);
    connect(ui->pushButton,&QPushButton::clicked,this,&MainWindow::slotbtnclick);


}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu;
    QAction* action=new QAction(this);
    action->setText("test");

    QMenu* newmenu=menu.addMenu("new menu");
    newmenu->addAction(action);
    connect(action,SIGNAL(triggered(bool)),this,SLOT(slottext(bool)));
    menu.exec(event->globalPos());

//    delete menu;

}void MainWindow::slottext(bool)
{
    qDebug()<<"this is action";
}

void MainWindow::slotbtnclick()
{
    qDebug()<<"this is action";
    takeCentralWidget();
    setCentralWidget(oldWidget);
}
