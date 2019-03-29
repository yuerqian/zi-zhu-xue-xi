#include "trackdelegate.h"
#include<QTextOption>
#include<QPainter>
#include<QTimeEdit>
#include<QDebug>

TrackDelegate::TrackDelegate(int durationColumn,QObject* parent):QStyledItemDelegate(parent)
{
    this->durationColumn=durationColumn;
}

void TrackDelegate::paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    if(index.column()==durationColumn)//对某一列进行重新绘画
    {
        int secs=index.model()->data(index,Qt::DisplayRole).toInt();
        QString text=QString("%1:%2").arg(secs/60,2,10,QChar('0')).arg(secs%60,2,10,QChar('0'));
        QTextOption o(Qt::AlignRight | Qt::AlignVCenter);
        painter->drawText(option.rect,text,o);
    }else
    {
        QStyledItemDelegate::paint(painter,option,index);
    }
}
//创建组件，当需要修改数据时触发，创建编辑器，编辑器返回创建新widget（组件）作为item项
QWidget* TrackDelegate::createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const
{
    qDebug()<<__FUNCTION__;
    if(index.column()==durationColumn)
    {
        QTimeEdit* timeEdit=new QTimeEdit(parent);
        timeEdit->setDisplayFormat("mm:ss");
        connect(timeEdit,SIGNAL(editingFinished()),this,SLOT(CommitAndCloseEditor()));//时间控件编辑完成时触发
        return timeEdit;
    }else
    {
        return QStyledItemDelegate::createEditor(parent,option,index);
    }
}
void TrackDelegate::CommitAndCloseEditor()
{
    qDebug()<<__FUNCTION__;
    QTimeEdit* edit=qobject_cast<QTimeEdit*>(sender());
    emit commitData(edit);//提交数据,当控件编辑器完成数据编辑时，必须发出此信号,告诉model将数据写入。
    emit closeEditor(edit);//告诉组件关闭编辑器
}
//编辑组件，当需要修改数据时触发，一般在createEditor或者setModelData调用后调用，设置编辑器（也就是createEditor返回新widget）的数据，也可以说是在view看到的widget效果
void TrackDelegate::setEditorData(QWidget *editor, const QModelIndex &index) const
{
    qDebug()<<__FUNCTION__;
    if(index.column()==durationColumn)
    {
        int secs=index.model()->data(index,Qt::DisplayRole).toInt();//获得model的数据
        QTimeEdit* timeEdit=qobject_cast<QTimeEdit*>(editor);//获得编辑器的组件
        timeEdit->setTime(QTime(0,secs/60,secs%60));
    }else{
        QStyledItemDelegate::setEditorData(editor,index);
    }
}
//获取组件的值来设置model值，设置完model数据之后会自动调用setEditorData设置view视图的值
void TrackDelegate::setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const
{
    qDebug()<<__FUNCTION__;
    if(index.column()==durationColumn)
    {
        QTimeEdit* timeEdit=qobject_cast<QTimeEdit*>(editor);//获取组件
        QTime time=timeEdit->time();
        int secs=(time.minute()*60)+time.second();
        model->setData(index,secs);//改变model的值
    }else{
        QStyledItemDelegate::setModelData(editor,model,index);
    }
}
