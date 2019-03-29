#ifndef CURRENCYMODEL_H
#define CURRENCYMODEL_H

#include <QWidget>
#include<QAbstractTableModel>
#include<QMap>

class CurrencyModel : public QAbstractTableModel
{
public:
    CurrencyModel(QObject *parent=0);

    void SetCurrencyMap(const QMap<QString,double> &map);


    //重载函数
    int rowCount(const QModelIndex &parent) const;//行数
    int columnCount(const QModelIndex &parent) const;//列数
    QVariant data(const QModelIndex &index, int role) const;//行列的信息，和role数据（并不是数据内容，而是每个数据元素的属性）
    QVariant headerData(int section, Qt::Orientation orientation, int role) const;//列头数据
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);

private:
    QString currencyAt(int offset) const;
    QMap<QString,double> CurrencyMap;

};

#endif // CURRENCYMODEL_H
