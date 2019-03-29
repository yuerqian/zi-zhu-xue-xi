#ifndef TRACKDELEGATE_H
#define TRACKDELEGATE_H

#include<QStyledItemDelegate>

class TrackDelegate : public QStyledItemDelegate
{
        Q_OBJECT
public:
    TrackDelegate(int durationColumn,QObject* parent=0);
    //重新绘画view视图
    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    //创建一个编辑器（实际返回一个新创建的组件）
    QWidget* createEditor(QWidget *parent, const QStyleOptionViewItem &option, const QModelIndex &index) const;
    //编辑一个编辑器（实际设置新创建组件的数据）
    void setEditorData(QWidget *editor, const QModelIndex &index) const;
    //数据设置到model里
    void setModelData(QWidget *editor, QAbstractItemModel *model, const QModelIndex &index) const;

private slots:
    void CommitAndCloseEditor();//提交编辑器的数据和关闭编辑

private:
    int durationColumn;//第几列的数据
};

#endif // TRACKDELEGATE_H
