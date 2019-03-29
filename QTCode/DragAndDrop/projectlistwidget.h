#ifndef PROJECTLISTWIDGET_H
#define PROJECTLISTWIDGET_H

#include<QListWidget>
#include<QMouseEvent>

class projectListWidget : public QListWidget
{
    Q_OBJECT
public:
    projectListWidget();

protected:
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void dragEnterEvent(QDragEnterEvent* e);
    void dragMoveEvent(QDragMoveEvent* e);
    void dropEvent(QDropEvent* e);

private:
    void performDrag();
    QPoint startPoint;
};

#endif // PROJECTLISTWIDGET_H
