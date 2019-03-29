#include "citymodel.h"

CityModel::CityModel(QObject* parent):QAbstractTableModel(parent)
{

}
void CityModel::setCities(const QStringList &cityNames)
{
    cities=cityNames;
    distances.resize(cities.count()*(cities.count()-1)/2);
    distances.fill(0);
}
int CityModel::rowCount(const QModelIndex &parent) const
{
    return cities.count();
}
int CityModel::columnCount(const QModelIndex &parent) const
{
    return cities.count();
}
QVariant CityModel::data(const QModelIndex &index, int role) const
{
    if(!index.isValid())
        return QVariant();
    if(role==Qt::TextAlignmentRole)//对齐方式
    {
        return int(Qt::AlignRight|Qt::AlignVCenter);
    }
    else if(role==Qt::DisplayRole)//文本显示属性
    {
        if(index.row()==index.column())
            return 0;
        int offset=offsetOf(index.row(),index.column());
        return distances[offset];

    }
    return QVariant();
}
bool CityModel::setData(const QModelIndex &index, const QVariant &value, int role)
{

}
QVariant CityModel::headerData(int section, Qt::Orientation orientation, int role) const
{

}
//在实际创建编辑器之前，view需要检测这个数据项是不是允许编辑。模型必须让view知道这一点，这是通过返回模型中每个数据项的标记 flag 来实现的
Qt::ItemFlags CityModel::flags(const QModelIndex &index) const
{
    Qt::ItemFlags flags=QAbstractTableModel::flags(index);//获取model的标记flag
    if(index.row()!=index.column())//当行列不相等时
    {
        flags|=Qt::ItemIsEditable;//加上可编辑的标记
    }
    return flags;
}
int CityModel::offsetOf(int row,int column) const
{
    if(row<column)
        qSwap(row,column);//两个数据交换

    return (row*(row-1)/2)+column;
}
