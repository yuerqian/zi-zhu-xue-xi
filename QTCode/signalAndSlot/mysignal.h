#ifndef MYSIGNAL_H
#define MYSIGNAL_H

#include <QObject>

class Mysignal : public QObject
{
    Q_OBJECT
public:
    explicit Mysignal(QObject *parent = nullptr);

signals:
    void sig();

public slots:
};

#endif // MYSIGNAL_H
