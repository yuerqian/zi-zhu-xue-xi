#ifndef APPLICATIONDATA_H
#define APPLICATIONDATA_H

#include <QObject>
#include<QDateTime>

class ApplicationData : public QObject
{
    Q_OBJECT
public:
    explicit ApplicationData(QObject *parent = nullptr);

public:
    Q_INVOKABLE QString getCurrentDateTime() const{
        QString time=QDateTime::currentDateTime().toString("yy-MM-dd/hh:mm:ss");
        return time;

    }

signals:

public slots:
    QString getCurrentDateTime2() const{
            QString time=QDateTime::currentDateTime().toString("yy-MM-dd/hh:mm:ss");
            return time;

        }

};

#endif // APPLICATIONDATA_H
