#ifndef MYEVENT_H
#define MYEVENT_H

#include <QWidget>
#include<QPushButton>
#include<QDebug>

class MyEvent : public QWidget
{
    Q_OBJECT
public:
    explicit MyEvent(QWidget *parent = nullptr);
    bool event(QEvent *event);
    void mousePressEvent(QMouseEvent* event);
   // void mouseDoubleClickEvent();//双击建议不要用，因为包括了两次单击按下和松开
    void keyPressEvent(QKeyEvent* keyevent);

    void mouseMoveEvent(QMouseEvent* mousemoveEvent);
    QPushButton* button;

    void closeEvent(QCloseEvent *mCloseEvent);//关闭系统
    void showEvent(QShowEvent* mShowEvnt);
    void hideEvent(QHideEvent* mHideEvent);
    void paintEvent(QPaintEvent* mPaintEvent);

signals:

public slots:

};
#endif // MYEVENT_H
