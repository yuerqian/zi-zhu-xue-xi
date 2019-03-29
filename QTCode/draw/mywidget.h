#ifndef MYWIDGET_H
#define MYWIDGET_H
#include<QWidget>
#include "mybutton.h"


class Mywidget:public QWidget
{
    Q_OBJECT
public:
    explicit Mywidget(QWidget *parent = nullptr);
    void paintEvent(QPaintEvent *);
    void mouseMoveEvent(QMouseEvent* ev);
    void mousePressEvent(QMouseEvent*);
    void mouseReleaseEvent(QMouseEvent*);
    QVector<QVector<QPoint>> _line;

    Mybutton* button;

signals:

public slots:
    void slotbuttonclicked();
};

#endif // MYWIDGET_H
