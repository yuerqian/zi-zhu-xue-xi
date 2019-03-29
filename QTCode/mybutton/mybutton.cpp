#include "mybutton.h"
#include<QPainter>
#include<QMouseEvent>

Mybutton::Mybutton(QWidget* parent):QWidget(parent)
{
    m_pressed=false;
    this->setGeometry(_rect);//设置控件位置

}
Mybutton::Mybutton(const QString& text,QWidget* parent):QWidget(parent),_rect(0,0,100,30),_text(text)
{
    m_pressed=false;
    this->setGeometry(_rect);

}
void Mybutton::mousePressEvent(QMouseEvent *e)
{
    m_pressed=true;
    update();


}
void Mybutton::mouseReleaseEvent(QMouseEvent *e)
{
    m_pressed=false;
    update();
    //判断鼠标释放时鼠标是否在控件内
    if(_rect.contains(e->pos()))
    {
        emit clicked();//发送点击事件信号
    }

}
void Mybutton::paintEvent(QPaintEvent*)
{
    QPainter p(this);
    if(m_pressed)
    {
        p.setBrush(Qt::yellow);
    }
    else
    {
        p.setBrush(Qt::darkGray);
    }

    p.drawRect(_rect);
    p.drawText(_rect,_text,QTextOption(Qt::AlignCenter));

}

