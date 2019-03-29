#include "myevent.h"
#include<QApplication>
#include<QDebug>
#include<QMouseEvent>
#include<QHBoxLayout>
#include<QLineEdit>
/*事件的响应流程：QMouseEvent->具体应该处理的窗口的event函数->event()根据消息类型来调用具体的虚函数*/

#include<QPainter>

MyEvent::MyEvent(QWidget *parent) : QWidget(parent)
{
    QHBoxLayout* layout=new QHBoxLayout(this);
    QPushButton* button2;
    QLineEdit* lineEdit;
    layout->addWidget(lineEdit=new QLineEdit());
    layout->addWidget(button=new QPushButton("button",this));
    layout->addWidget(button2=new QPushButton("button2",this));
   // button->setFocus();//这种方式设置焦点会响应鼠标消息，但不会响应键盘消息，因为按钮不处理键盘消息
    button->setDefault(true);//这种方式设置焦点会响应鼠标消息，也会响应键盘消息
    connect(button,&QPushButton::clicked,[](){
        qDebug()<<"button clicked";
    });
    connect(button2,&QPushButton::clicked,[](){
        qDebug()<<"button2 clicked";
    });
    connect(lineEdit,&QLineEdit::returnPressed,[](){
        qDebug()<<"QLineEdit ";
    });

    //this->setMouseTracking(true);设置鼠标移动时就触发mousePressEvent事件，不需要按下才触发
    this->setMouseTracking(true);

}
bool MyEvent::event(QEvent *event)
{
    //一般不是用Event重载的方式，建议只重写事件处理器
//    if(event->type()==QEvent::MouseButtonPress)
//    {
//        qDebug()<<"mouse press";
//        return true;
//    }
    event->accept();//表示已经处理了消息，不再继续传递
    return QWidget::event(event);
}
void MyEvent::mousePressEvent(QMouseEvent *event)
{

    qDebug()<<event->pos();
    //是否按下左键
    if(event->button()==Qt::LeftButton)
    {

    }
    //是否按下shif+左键
    if(event->modifiers()==Qt::ShiftModifier)
    {
        qDebug()<<"shift press";
        return;
    }
    //在按钮上点击不会触发鼠标事件，因为事件重写的是父窗口的事件，并没有重写按钮子窗口的鼠标事件
}
void MyEvent::keyPressEvent(QKeyEvent *keyevent)
{
    keyevent->accept();//表示已经处理了消息，不再继续传递，很少用
    keyevent->ignore();//表示忽略该消息，很少用
    int key=keyevent->key();
    qDebug()<<key;
    qDebug()<<(char)key;
    //是否可以响应键盘事件，看焦点在哪个窗口上，如果焦点在父窗口上则会响应这个事件，如果在按键上，则响应的是按键绑定的槽函数
}
void MyEvent::mouseMoveEvent(QMouseEvent* mousemoveEvent)
{
    //为什么要按着鼠标移动之后才能在mouseMoveEvent()函数中显示鼠标坐标值？通过this->setMouseTracking(true);设置鼠标移动时就触发mousePressEvent事件，不需要按下
    static int a=0;
    qDebug()<<"Mouse move"<<a++;

}
void MyEvent::closeEvent(QCloseEvent* mcloseEvent)
{
    qDebug()<<"close event";
}
void MyEvent::showEvent(QShowEvent *mShowEvnt)
{
    qDebug()<<"show Event";
}
void MyEvent::hideEvent(QHideEvent *mHideEvent)
{
    qDebug()<<"hide Event";
}
//重绘
void MyEvent::paintEvent(QPaintEvent* mPaintEvent)
{
    QPainter p(this);//设备上下文，可以在窗口（QWidget）上绘画，也可以在QPaintDevice（比如图片，打印机）上绘画，因为QWidget派生于QPaintDevice
    p.drawLine(QPoint(0,0),QPoint(100,100));

}
int main(int argc,char*argv[])
{
    QApplication app(argc,argv);
    MyEvent w;
    w.show();
    return app.exec();
}
