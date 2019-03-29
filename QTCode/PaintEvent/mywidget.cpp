#include "mywidget.h"
#include<QPainter>
#include<QApplication>

MyWidget::MyWidget(QWidget *parent) : QWidget(parent)
{

}
void MyWidget::paintEvent(QPaintEvent *)
{
    //paintEvent，做导航和屏幕共享的时候用的比较多

//复杂功能
    //将要绘制的内容先绘制到一张图片里，然后再画到窗口上去，这样就可以将要绘制的内容分成一块一块的，重绘时就不需要全部重绘
    QPixmap pixmap(size());
    QPainter p(&pixmap);//先绘制到一张图片里去，然后再画到窗口上

    //只能通过在开始前先画个矩形出来作为背景，否则没有背景是黑色
    QPalette pal    = this->palette();
    QBrush brush = pal.background();//获取主窗口的背景色

    p.setBrush(brush);
    p.drawRect(rect());


    //旋转,缩放，平移,可以多次设置p.setTransform(transform);但是第二个参数设置为true，p.setTransform(transform，true);false则会将上一个覆盖掉
//    QTransform transform;
//    transform.rotate(30);
//    transform.translate(10,10);
//    transform.scale(0.5,0.5);
//    p.setTransform(transform);

    //设置原点,整体平移，只移动设置之后的，设置之前的不影响
//    p.translate(100,100);

    //消去锯齿
    p.setRenderHint(QPainter::Antialiasing);

//简单功能
    //捉取不同的工具绘制
//    p.setPen(QPen(Qt::red,2,Qt::DashLine));//改变全局的画笔
//    p.setBrush(brush_gra);//画刷，改变的是封闭图形的
//    p.setFont(QFont("aaa",30,20,true));//改变文字样式，1（参数）字体，没有找到则是默认字体，2大小，3粗体大小，4倾斜

    //线性渐变
//    QLinearGradient gradient_line(60,50,200,200);//设置点（60,50）到点（200,200）的渐变
//    gradient_line.setColorAt(0.2,Qt::gray);
//    gradient_line.setColorAt(0.6,Qt::red);
//    gradient_line.setColorAt(1,Qt::yellow);

    QRadialGradient gradient(300,300,50,0,0);
    gradient.setColorAt(0,Qt::red);//从0开始到1的渐变
    gradient.setColorAt(0.5,Qt::green);//从0开始到1的渐变
    gradient.setColorAt(1,Qt::yellow);

//    //角度渐变
//    QConicalGradient conicalGradient(300, 300, 0);
//    conicalGradient.setColorAt(0.0, Qt::red);
//    conicalGradient.setColorAt(60.0/360.0, Qt::yellow);
//    conicalGradient.setColorAt(120.0/360.0, Qt::green);
//    conicalGradient.setColorAt(180.0/360.0, Qt::cyan);
//    conicalGradient.setColorAt(240.0/360.0, Qt::blue);
//    conicalGradient.setColorAt(300.0/360.0, Qt::magenta);
//    conicalGradient.setColorAt(1.0, Qt::red);

    QBrush brush_gra(gradient);
    p.setBrush(brush_gra);
    p.save();
    //画东西
    p.drawLine(QPoint(0,0),QPoint(100,100));//划线
    p.translate(100,100);
    p.drawEllipse(QPoint(300,300),150,130);//椭圆
    p.save();
    p.restore();
    p.restore();
    p.drawEllipse(QPoint(300,300),150,130);//椭圆
    p.drawText(QPoint(300,300),"你好");//文字
//    p.drawPixmap(QPoint(100,100),QPixmap("../aaa.png"));//图片
//    p.drawRect(QRect(40,40,80,70));//矩形
//    p.drawRoundedRect(QRect(40,60,100,50),20,5);//圆角矩形



    p.end();//图片绘制结束

    p.begin(this);//开始绘制到窗口上去
//    QPainter p(this);
    p.drawPixmap(0,0,pixmap);//将图片绘制到窗口上



}
void MyWidget::mouseMoveEvent(QMouseEvent* ev)
{


}
int main(int argc,char*argv[])
{
    QApplication app(argc,argv);
    MyWidget w;
    w.show();
    return app.exec();
}
