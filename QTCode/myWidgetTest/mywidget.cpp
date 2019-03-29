#include "mywidget.h"
#include<QDebug>
#include<QComboBox>
#include<QPushButton>
#include<QTreeWidget>


mywidget::mywidget(QWidget *parent) : QWidget(parent)
{

#if 0
    QListWidget *pListWidget = new QListWidget(this);//列表
    int i = 0;
    do {
        ++i;
        QListWidgetItem *pItem = new QListWidgetItem(pListWidget);//列表项，每个控件可以有多个角色值（Qt::UserRole）
        pItem->setData(Qt::UserRole, i);  // 用户数据,Qt::UserRole表示第一个角色值（即是第一个绑定的值）
        qDebug() << "ID : " << Qt::UserRole<<i;
        pItem->setData(Qt::UserRole + 1, QString("Qter %1").arg(i));  // 用户数据，Qt::UserRole+1表示第二个角色值
        pItem->setText(QString("Item %1").arg(i));  // 文本
        pListWidget->addItem(pItem);
    } while (i < 5);

    // 连接信号槽
    connect(pListWidget, &QListWidget::itemClicked, this, &mywidget::onItemClicked);
#endif

#if 0
    QListWidget *pListWidget = new QListWidget(this);
    int i = 0;
    do {
        ++i;
        QListWidgetItem *pItem = new QListWidgetItem(pListWidget);
        User user;
        user.nID = i;
        user.strName = QString("Qter %1").arg(i);
        //如果想要自定义的消息类型（比如User类型）能够在QVariant中使用，则必须通过Q_DECLARE_METATYPE注册，才可以。
        pItem->setData(Qt::UserRole, QVariant::fromValue(user));  // 给QVariant类型设置用户数据（相当于Setvalue()),只有一个角色值和结构体体绑定
        pItem->setText(QString("Item %1").arg(i));
        pListWidget->addItem(pItem);
    } while (i < 5);
    // 连接信号槽
    connect(pListWidget, &QListWidget::itemClicked, this, &mywidget::onItemClicked);
#endif

    #if 0
    QComboBox *pComboBox = new QComboBox(this);
    pComboBox->addItem("Chinese");
    pComboBox->addItem("English");
    pComboBox->setItemData(0, QVariant::fromValue(UI_ZH));  // 设置用户数据
    pComboBox->setItemData(1, QVariant::fromValue(UI_EN));  // 设置用户数据

    // 连接信号槽,currentIndexChanged信号被重载，要强制类型转换
    connect(pComboBox, static_cast<void (QComboBox::*)(int)>(&QComboBox::currentIndexChanged), this, &mywidget::onCurrentIndexChanged);
    #endif

#if 0
    QPushButton *pButton = new QPushButton(this);
    pButton->setText("Qter");

    // 用户数据
    User *pUser = new User();
    pUser->nID = 1;
    pUser->strName = "Qter";

    pButton->setUserData(Qt::UserRole, pUser);  // 设置用户数据

    // 连接信号槽
    connect(pButton, &QPushButton::clicked, this, &mywidget::onClicked);
#endif

    QTreeWidget* tree=new QTreeWidget(this);
    tree->setColumnCount(4);
    QTreeWidgetItem* root=new QTreeWidgetItem(tree,QStringList("root"));
    QTreeWidgetItem* leaf=new QTreeWidgetItem(root,QStringList("leaf1"));
    QTreeWidgetItem* leaf2=new QTreeWidgetItem(root,QStringList("leaf2"));
    root->addChild(leaf2);


}

void mywidget::onItemClicked(QListWidgetItem *item) {
#if 0
    int nID = item->data(Qt::UserRole).toInt();  // 获取用户数据
    QString strName = item->data(Qt::UserRole + 1).toString();  // 获取用户数据

    qDebug() << "ID : " << nID;
    qDebug() << "Name : " << strName;
#endif


    QVariant variant = item->data(Qt::UserRole);  // 获取用户数据
    User user = variant.value<User>();

    qDebug() << "ID : " << user.nID;
    qDebug() << "Name : " << user.strName;



}

void  mywidget::onCurrentIndexChanged(int index) {
    // 获取发送者
    QObject *pObject = this->sender();
    QComboBox *pComboBox = qobject_cast<QComboBox *>(pObject);

    // 获取用户数据
    QVariant variant = pComboBox->itemData(index);
    LANGUAGE language = variant.value<LANGUAGE>();

    qDebug() << "Language : " << language;
}

void mywidget::onClicked() {
    // 获取发送者
    QObject *pObject = this->sender();
    QPushButton *pButton = qobject_cast<QPushButton *>(pObject);

    // 获取用户数据,要强制转换
//    User *pUser = (User *)(pButton->userData(Qt::UserRole));
    //尽量使用安全的强制转换static_cast
    User *pUser = static_cast<User*>(pButton->userData(Qt::UserRole));



    qDebug() << "ID : " << pUser->nID;
    qDebug() << "Name : " << pUser->strName;
}


