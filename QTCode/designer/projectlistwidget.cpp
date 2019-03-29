#include "projectlistwidget.h"
#include<QApplication>
#include<QMimeData>
#include<QDrag>
#include<QDebug>
#include<mymimedata.h>


projectListWidget::projectListWidget(QWidget* parent):QListWidget(parent)
{
    setAcceptDrops(true);
}

void projectListWidget::mousePressEvent(QMouseEvent *e)
{
    qDebug()<<"mousePressEvent"<<e->button();
    if(e->button()==Qt::LeftButton)
    {
        startPoint=e->pos();//记录鼠标按下的位置
        qDebug()<<"mousePressEvent"<<startPoint;
    }
    QListWidget::mousePressEvent(e);//调用系统自带的处理函数，实现正常鼠标操作，否则会被鼠标事件会被屏蔽
}
void projectListWidget::mouseMoveEvent(QMouseEvent *e)
{
    qDebug()<<"mouseMoveEvent"<<e->button();
    if(e->buttons()==Qt::LeftButton)//注意：e->button()对于移动鼠标事件来说总是返回Qt::NoButton
    {
            qDebug()<<"mouseMoveEvent"<<startPoint;
        int distance=(e->pos()-startPoint).manhattanLength();//求两点之间的向量距离
        if(distance>=QApplication::startDragDistance())//认为是拖放操作的距离,通常是4px(像素)
            performDrag();
    }
    QListWidget::mouseMoveEvent(e);
}

void projectListWidget::performDrag()
{

    QListWidgetItem* item=currentItem();
    qDebug()<<"performDrag"<<item;
    if((item))
    {
        MyMimeData *mimeData=new MyMimeData(this);//将需要拖动的数据放入QMimedata对象中，该对象用于保存需要传递的数据，数据的内容完全由程序员自行设定。通常为界面上所选择内容。
        //mimeData->setText(item->text());//设置拖动时传递的具体数据
        mimeData->setData("text/csv",item->text().toUtf8());
        mimeData->setData("newtype",item->text().toUtf8());
        QDrag* drag=new QDrag(this);//拖动类型
        drag->setMimeData(mimeData);//设置拖动的数据QMimeData
        //drag->setDragCursor(QPixmap("E:\\QTCode\\aaa.png"),Qt::CopyAction);//改变鼠标光标的样式
        //drag->setPixmap(QPixmap("E:\\QTCode\\aaa.png"));//用图片来表示拖动的数据
        //drag->setHotSpot(QPoint(10,10));//改变鼠标光标在表示数据的图片上的位置
        Qt::DropAction Action=drag->exec(Qt::MoveAction|Qt::CopyAction|Qt::LinkAction);
        //drag->target();//返回拖放的目标控件，即把拖放对象放下的控件
        qDebug()<<"222222222:"<<Action;
        if(Action==Qt::MoveAction)//开始拖动数据，第一参数是支持拖放的动作。
            delete item;

    }
}

void projectListWidget::dragEnterEvent(QDragEnterEvent *e)
{

    projectListWidget* source=qobject_cast<projectListWidget *>(e->source());//将拖放的内容转换为projectListWidget类型
    qDebug()<<"dragEnterEvent"<<source;
    if(source&&source!=this)
    {
        //要允许拖放，必须调用e->setAccepted(Qt::MoveAction);或者e->accept();两者效果一致
        //e->setAccepted(Qt::CopyAction);
        //e->setDropAction(Qt::CopyAction);
        e->accept();
        //e->ignore();//表示不接受拖放
    }
}

void projectListWidget::dragMoveEvent(QDragMoveEvent *e)
{
    qDebug()<<"dragMoveEvent";
    projectListWidget* source=qobject_cast<projectListWidget*>(e->source());//将拖放的内容转换为projectListWidget类型
    if(source&&source!=this)
    {
        qDebug()<<"afadfasdf:"<<e->dropAction();
        e->setDropAction(Qt::CopyAction);//用来改变拖放显示的图标，但设置的动作无效
        //e->setAccepted(Qt::MoveAction);//与e->accept();的效果一致
        //在指定的矩形区域内接受数据
        QRect r(0,0,111,33);
        if(r.contains(e->pos()))
        {
            e->accept()	;
        }
        else
            e->ignore();
        //e->accept();
        //e->ignore();//如果移动中不接受拖放则放弃拖放
    }
}

void projectListWidget::dropEvent(QDropEvent *e)
{
     qDebug()<<"dropEvent";
    projectListWidget* source=qobject_cast<projectListWidget*>(e->source());//将拖放的内容转换为projectListWidget类型
    const MyMimeData* myMimeData=qobject_cast<const MyMimeData*>(e->mimeData());
    if(source && source!=this && myMimeData)
    {
        qDebug()<<"dropEvent2";
        addItem(e->mimeData()->text());//得到拖动的数据
        addItem(e->mimeData()->data("text/csv"));//得到拖动的数据
        addItem(e->mimeData()->data("newtype"));//得到拖动的数据
        e->setDropAction(Qt::CopyAction);//实际拖放动作在放下dropEvent()函数中使用QDropEvent::setDropAction()函数(还需在之后调用accept()函数,否则drag->exec()的返回值是IgnoreAction)设置
        //e->setAccepted(Qt::CopyAction);
        e->accept();
        //e->acceptProposedAction();

    }
     if(e->mimeData()->hasFormat("text/csv"))
         qDebug()<<"================================";
}








