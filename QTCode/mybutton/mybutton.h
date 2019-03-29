#ifndef MYBUTTON_H
#define MYBUTTON_H
#include<QWidget>


class Mybutton:public QWidget
{
    Q_OBJECT
public:
    explicit Mybutton(QWidget* parent=nullptr);
    Mybutton(const QString& text,QWidget* parent=nullptr);
    QRect _rect;//位置
    QString _text=NULL;//文本
    void paintEvent(QPaintEvent*);
    bool m_pressed=false;//判断是否按下，做出闪烁效果
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);

signals:
    void clicked();//信号的形式触发事件，替代visturl void clicked()虚函数的形式避免多次重写

public slots:
};

#endif // MYBUTTON_H
