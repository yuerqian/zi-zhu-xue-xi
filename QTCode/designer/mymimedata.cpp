#include "mymimedata.h"

MyMimeData::MyMimeData(const QListWidget* ListWidget)
{
    myListWidget=ListWidget;
    myFormat<<"text/csv"<<"text/html"<<"text/plain"<<"newtype";
}
QVariant MyMimeData::retrieveData(const QString &mimetype, QVariant::Type preferredType) const
{
    if(mimetype=="text/csv")
    {
        return myListWidget->currentItem()->text();
    }
    else if(mimetype=="text/html")
    {
        return myListWidget->currentItem()->text();
    }else if(mimetype=="text/plain")
    {
        return myListWidget->currentItem()->text();
    }else if(mimetype=="newtype")//新类型返回的拖放数据
    {
        return myListWidget->currentItem()->text();
    }
    else
    {
        return QMimeData::retrieveData(mimetype,preferredType);//不感兴趣的数据类型记得交给
    }
}
