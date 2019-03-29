#ifndef PROJECTLISTWIDGET_H
#define PROJECTLISTWIDGET_H

#include<QListWidget>
#include<QMouseEvent>
#include<projectlistwidget.h>

class projectListWidget : public QListWidget
{
    Q_OBJECT
public:
    projectListWidget(QWidget* parent);

protected:
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void dragEnterEvent(QDragEnterEvent* e);//发起拖放操作
    void dragMoveEvent(QDragMoveEvent* e);
    void dropEvent(QDropEvent* e);//接收拖放数据

private:
    void performDrag();//拖放类构造，开始
    QPoint startPoint;//拖放的起始位置
};

#endif // PROJECTLISTWIDGET_H
