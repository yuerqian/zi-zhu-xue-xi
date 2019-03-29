#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include<QPushButton>

class MyWidget : public QWidget
{
    Q_OBJECT  //包括信号和槽
public:
    explicit MyWidget(QWidget *parent = nullptr);
    bool eventFilter(QObject *watched, QEvent *event);
    QPushButton* button;
    bool event(QEvent *event);//postevent没有对应的虚函数，只能通过重写event函数，处理消息

signals:

public slots:
};

#endif // MYWIDGET_H
