#include "chooseinterface.h"
#include<QNetworkInterface>
#include<QHBoxLayout>

chooseInterface::chooseInterface(QWidget *parent):QDialog(parent)
{
    //第一种方法QNetworkInterface::allAddresses()，获取所有的IP
    QList<QHostAddress> hostList=QNetworkInterface::allAddresses();//获取网卡的所有ip
//    //第二种方法QNetworkInterface::allInterfaces(),获取网卡ip
//    QList<QNetworkInterface> List=QNetworkInterface::allInterfaces();
//    QList<QNetworkAddressEntry> entryList=List.at(0).addressEntries();
//    QHostAddress Addr=entryList.at(0).ip();

    QHBoxLayout* lay=new QHBoxLayout(this);
    _comboBox=new QComboBox;
    lay->addWidget(_comboBox);


    foreach (QHostAddress addr, hostList) {
        quint32 ipv4=addr.toIPv4Address();//获取所有ipv4协议的ip
        if(ipv4==0)//去掉0.0.0.0的ip
            continue;
        _comboBox->addItem(QHostAddress(ipv4).toString());

    }
    this->strSelect=_comboBox->currentText();//设置默认IP
    connect(_comboBox,SIGNAL(currentIndexChanged(QString)),this,SLOT(slotComboBoxChange(QString)));

}
void chooseInterface::slotComboBoxChange(QString str)
{
    this->strSelect=str;//设置改变后的ip


}
