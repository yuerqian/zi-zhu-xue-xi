#ifndef MYSLOT_H
#define MYSLOT_H

#include <QObject>

class MySlot : public QObject
{
    Q_OBJECT
public:
    explicit MySlot(QObject *parent = nullptr);
    int i=0;
    int i2=0;

signals:

public slots:
    void mySlot();
    void mySlot2();
};

#endif // MYSLOT_H
