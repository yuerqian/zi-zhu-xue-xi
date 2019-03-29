#include "mywidget.h"
#include<QApplication>
#include<QPainter>
#include<QMouseEvent>
#include<QtDebug>

Mywidget::Mywidget(QWidget *parent):QWidget(parent)
{
    button=new Mybutton("mybutton",this);
    connect(button,SIGNAL(clicked()),this,SLOT(slotbuttonclicked()));

}
void Mywidget::paintEvent(QPaintEvent *)
{
    QPainter p(this);
//    for(int i=0;i<_line.size()-1;i++)
//    {
//        p.drawLine(_line.at(i),_line.at(i+1));
//    }
    for(int i=0;i<_line.size();i++)
    {
        QVector<QPoint> line=_line.at(i);
        for(int j=0;j<line.size()-1;j++)
        {
            p.drawLine(line.at(j),line.at(j+1));
        }
    }

}
void Mywidget::slotbuttonclicked()
{
    qDebug()<<"button clicked";
}
void Mywidget::mouseMoveEvent(QMouseEvent* ev)
{
    //如果鼠标按下的时候，是在另一个控件上响应了mousePressEvent事件，容器里并没有线，_line.last()出错，这时可以添加一条线，表示在mouseReleaseEvent的时候开始画线
    if(_line.size()==0)
    {
        QVector<QPoint> line;
        _line.append(line);
    }
    //获取最后一条线的容器，然后往里面添加点
    QVector<QPoint>& lastline=_line.last();
    lastline.append(ev->pos());
    update();//强制重绘

}
void Mywidget::mousePressEvent(QMouseEvent *ev)
{
    //每次点击就重新添加一s个容器用来装一条线，并放入之前已经画过的线的容器的后面
    QVector<QPoint> line;
    _line.append(line);
    //取出画最后一条线的容器，然后往最后一条线的容器添加点，注意这里必须要用“&”的方法(引用，别名，操作的实际还是原来的内存空间），只有这样才可以操作到原来的容器（也就是_line)
    QVector<QPoint>& lastline=_line.last();
    lastline.append(ev->pos());
    update();

}
void Mywidget::mouseReleaseEvent(QMouseEvent *ev)
{
    //获取最后一条线的容器，然后往里面添加点
    QVector<QPoint>& lastline=_line.last();
    lastline.append(ev->pos());
    update();

}
int main(int argc,char*argv[])
{
    QApplication app(argc,argv);
    Mywidget w;
    w.show();
    return app.exec();
}
