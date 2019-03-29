#include "currencymodel.h"
#include<QDebug>

CurrencyModel::CurrencyModel(QObject* parent):QAbstractTableModel(parent)
{

}
int CurrencyModel::rowCount(const QModelIndex &parent) const
{
    qDebug()<<__FUNCTION__<<parent;
    return CurrencyMap.count();
}
int CurrencyModel::columnCount(const QModelIndex &parent) const
{
    qDebug()<<__FUNCTION__<<parent;
    return CurrencyMap.count();
}

QVariant CurrencyModel::data(const QModelIndex &index, int role) const
{
    qDebug()<<__FUNCTION__<<index<<role;
    if(!index.isValid())
        return QVariant();//返回空构造
    if(role==Qt::TextAlignmentRole)//对齐方式
    {
        return int(Qt::AlignRight|Qt::AlignVCenter);
    }
    else if(role==Qt::DisplayRole)//文本显示属性
    {

        QString rowCurrency=currencyAt(index.row());//根据重写的rowCount()函数可以知道有多少行,从0开始一行行增加，然后根据行数获取对应的key
        QString columnCurrency=currencyAt(index.column());//根据重写的rowCount()函数可以知道有多少行，从0开始一行行增加，然后根据行数获取对应的key
        //根据key取出里面的值，计算，返回
        if(CurrencyMap.value(rowCurrency)==0.0)
            return "####";
        double amount=CurrencyMap.value(columnCurrency)/CurrencyMap.value(rowCurrency);//计算汇率
        return QString("%1").arg(amount,0,'f',4);//返回显示的数据
    }

    return QVariant();
}

QVariant CurrencyModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    qDebug()<<__FUNCTION__;
    if(role!=Qt::DisplayRole)//非显示属性
    {
        return QVariant();
    }
    return currencyAt(section);
}

QString CurrencyModel::currencyAt(int offset) const
{
    return (CurrencyMap.begin()+offset).key();
}
 void CurrencyModel::SetCurrencyMap(const QMap<QString, double> &map)
 {
     beginResetModel();//开始设置数据，告诉关心这个模型的其他类（比如view），重置数据，让其他类做好更新数据的准备
     CurrencyMap=map;
     endResetModel();//结束设置数据
 }

 //在实际创建编辑器之前，view需要检测这个数据项是不是允许编辑。模型必须让view知道这一点，这是通过返回模型中每个数据项的标记 flag 来实现的
 Qt::ItemFlags CurrencyModel::flags(const QModelIndex &index) const
 {
     qDebug()<<__FUNCTION__;
     Qt::ItemFlags flags=QAbstractTableModel::flags(index);//获取model的标记flag
     if(index.row()!=index.column())//当行列不相等时
     {
         flags|=Qt::ItemIsEditable;//加上可编辑的标记
     }
     return flags;
 }

bool CurrencyModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    qDebug()<<__FUNCTION__;
    if(index.isValid()&&role==Qt::EditRole&&index.row()!=index.column())
    {
        QString rowCurrency=headerData(index.row(),Qt::Vertical,Qt::DisplayRole).toString();//获取行的key
        QString columnCurrency=headerData(index.column(),Qt::Horizontal,Qt::DisplayRole).toString();//获取列头的key
        CurrencyMap.insert(columnCurrency,value.toDouble()*CurrencyMap.value(rowCurrency));//设置进入model的数据
        emit dataChanged(index,index);//发信号，告诉view，model数据发生改变
        return true;
    }
    return false;
}


