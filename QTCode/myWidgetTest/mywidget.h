#ifndef MYWIDGET_H
#define MYWIDGET_H

#include <QWidget>
#include<QListWidget>

// 用户信息
struct User : QObjectUserData {
    int nID;  // ID
    QString strName;  // 用户名
};

// 语言
typedef enum{
    UI_ZH,  // 中文
    UI_EN  // 英文
} LANGUAGE;

Q_DECLARE_METATYPE(User)   //如果想要自定义的消息类型（比如User类型）能够在QVariant中使用，则必须通过Q_DECLARE_METATYPE注册，才可以。
Q_DECLARE_METATYPE(LANGUAGE)

class mywidget : public QWidget
{
    Q_OBJECT
public:
    explicit mywidget(QWidget *parent = nullptr);

signals:

public slots:
    void onItemClicked(QListWidgetItem *item);
    void  onCurrentIndexChanged(int index);
    void onClicked();
};

#endif // MYWIDGET_H
