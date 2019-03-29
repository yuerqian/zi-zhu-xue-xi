#include "projectlistwidget.h"
#include<QApplication>
#include<QMimeData>
#include<QDrag>


projectListWidget::projectListWidget()
{
    setAcceptDrops(true);
}

void projectListWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        startPoint=e->pos();//记录鼠标按下的位置
    }
    QListWidget::mousePressEvent(e);//调用系统自带的处理函数，实现正常鼠标操作，否则会被鼠标事件会被屏蔽
}
void projectListWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(e->button()&Qt::LeftButton)
    {
        int distance=(e->pos()-startPoint).manhattanLength();//求两点之间的向量距离
        if(distance>=QApplication::startDragDistance())//认为是拖放操作的距离,通常是4px(像素)
            performDrag();
    }
    QListWidget::mouseMoveEvent(e);
}

void projectListWidget::performDrag()
{
    QListWidgetItem* item=currentItem();
    if((item))
    {
        QMimeData *mimeData=new QMimeData();
        mimeData->setText(item->text());
        QDrag* drag=new QDrag(this);
        drag->setMimeData(mimeData);
        //drag->setPixmap(":/images/person.png");
        if(drag->exec(Qt::MoveAction)==Qt::MoveAction)
            delete item;

    }
}

void projectListWidget::dragEnterEvent(QDragEnterEvent *e)
{
    projectListWidget* source=qobject_cast<projectListWidget *>(e->source());//将拖放的内容转换为projectListWidget类型
    if(source&&source!=this)
    {
        e->setAccepted(Qt::MoveAction);
        e->accept();
    }
}

void projectListWidget::dragMoveEvent(QDragMoveEvent *e)
{
    projectListWidget* source=qobject_cast<projectListWidget*>(e->source());//将拖放的内容转换为projectListWidget类型
    if(source&&source!=this)
    {
        e->setAccepted(Qt::MoveAction);
        e->accept();
    }
}

void projectListWidget::dropEvent(QDropEvent *e)
{
    projectListWidget* source=qobject_cast<projectListWidget*>(e->source());//将拖放的内容转换为projectListWidget类型
    if(source&&source!=this)
    {
        addItem(e->mimeData()->text());
        e->setAccepted(Qt::MoveAction);
        e->accept();
    }

}








