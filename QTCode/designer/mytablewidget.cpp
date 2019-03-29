#include "mytablewidget.h"
#include<QMimeData>
#include<QDrag>
#include<QDebug>
#include<QApplication>

MyTableWidget::MyTableWidget(QWidget* parent):QTableWidget(parent)
{
    setAcceptDrops(true);
}

void MyTableWidget::mousePressEvent(QMouseEvent *e)
{
    if(e->button()==Qt::LeftButton)
    {
        startPoint=e->pos();//记录鼠标按下的位置
    }
    MyTableWidget::mousePressEvent(e);//调用系统自带的处理函数，实现正常鼠标操作，否则会被鼠标事件会被屏蔽
}
void MyTableWidget::mouseMoveEvent(QMouseEvent *e)
{
    if(e->buttons()==Qt::LeftButton)//注意：e->button()对于移动鼠标事件来说总是返回Qt::NoButton
    {
        int distance=(e->pos()-startPoint).manhattanLength();//求两点之间的向量距离
        if(distance>=QApplication::startDragDistance())//认为是拖放操作的距离,通常是4px(像素)
            performDrag();
    }
    MyTableWidget::mouseMoveEvent(e);
}

void MyTableWidget::performDrag()
{
    QString strBuf="";
    //循环读取数据
    for(int i=0;i<rowCount();i++){
        for(int j=0;j<columnCount();j++){
            if(item(i,j)!=NULL){               //一定要先判断非空，否则会报错
                strBuf=strBuf+item(i,j)->text();
            }
        }
    }
    qDebug()<<"gogogogogog："<<strBuf;
    if(!strBuf.isEmpty())
    {
        QMimeData *mimeData=new QMimeData();//将需要拖动的数据放入QMimedata对象中，该对象用于保存需要传递的数据，数据的内容完全由程序员自行设定。通常为界面上所选择内容。
        mimeData->setText(strBuf);//设置拖动时传递的具体数据
        mimeData->setHtml(strBuf);
        mimeData->setData("text/csv",strBuf.toUtf8());
        QDrag* drag=new QDrag(this);//拖动类型
        drag->setMimeData(mimeData);//设置拖动的数据QMimeData
        //drag->setDragCursor(QPixmap("E:\\QTCode\\aaa.png"),Qt::CopyAction);//改变鼠标光标的样式
        //drag->setPixmap(QPixmap("E:\\QTCode\\aaa.png"));//用图片来表示拖动的数据
        //drag->setHotSpot(QPoint(10,10));//改变鼠标光标在表示数据的图片上的位置
        Qt::DropAction Action=drag->exec(Qt::MoveAction|Qt::CopyAction|Qt::LinkAction);
        //drag->target();//返回拖放的目标控件，即把拖放对象放下的控件
        qDebug()<<"222222222:"<<Action;
        //if(Action==Qt::MoveAction)//开始拖动数据，第一参数是支持拖放的动作。

    }
}

void MyTableWidget::dragEnterEvent(QDragEnterEvent *e)
{

    MyTableWidget* source=qobject_cast<MyTableWidget *>(e->source());//将拖放的内容转换为projectListWidget类型
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

void MyTableWidget::dragMoveEvent(QDragMoveEvent *e)
{
    qDebug()<<"dragMoveEvent";
    MyTableWidget* source=qobject_cast<MyTableWidget*>(e->source());//将拖放的内容转换为projectListWidget类型
    if(source&&source!=this)
    {
        qDebug()<<"afadfasdf:"<<e->dropAction();
        e->setDropAction(Qt::CopyAction);//用来改变拖放显示的图标，但设置的动作无效
        //e->setAccepted(Qt::MoveAction);//与e->accept();的效果一致
        //在指定的矩形区域内接受数据
        QRect r(0,0,111,332);
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

void MyTableWidget::dropEvent(QDropEvent *e)
{
     qDebug()<<"dropEvent";
    MyTableWidget* source=qobject_cast<MyTableWidget*>(e->source());//将拖放的内容转换为projectListWidget类型
    if(source&&source!=this)
    {
        if(e->mimeData()->hasFormat("text/csv"))
        {
            qDebug()<<"hhhhhh:"<<e->mimeData()->data("text/csv");//得到拖动的数据
            e->setDropAction(Qt::CopyAction);//实际拖放动作在放下dropEvent()函数中使用QDropEvent::setDropAction()函数(还需在之后调用accept()函数,否则drag->exec()的返回值是IgnoreAction)设置
            e->accept();
        }
    }

}

QString MyTableWidget::toHtml(const QString& strBuf)
{

}

QString MyTableWidget::toCsv(const QString& strBuf)
{

}
