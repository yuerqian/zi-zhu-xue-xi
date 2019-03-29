#ifndef MYMIMEDATA_H
#define MYMIMEDATA_H
#include<QMimeData>
#include<QListWidget>

class MyMimeData : public QMimeData
{
    Q_OBJECT
public:
    MyMimeData(const QListWidget* ListWidget);

private:
    const QListWidget* myListWidget;//用来得到正确的数据，返回给获取拖放数据的函数
    QStringList myFormat;//构造新的数据类型

public:
    QStringList formats() const//重载函数,用来构造新的数据类型，返回数据类型的列表
    {
        return myFormat;
    }
protected:
    QVariant retrieveData(const QString &mimetype, QVariant::Type preferredType) const;//重载函数，可以决定放回的拖放数据
};

#endif // MYMIMEDATA_H
