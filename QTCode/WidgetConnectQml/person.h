#ifndef PERSON_H
#define PERSON_H

#include <QObject>
#include<QDebug>
// 身份证
class IDCard : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString number READ number WRITE setNumber)
    Q_PROPERTY(QString validDate READ validDate WRITE setValidDate NOTIFY validDateChanged)

public:
    void setNumber(const QString &number) {
        if (number != m_number)
            m_number = number;
    }
    QString number() const {
        return m_number;
    }

    void setValidDate(const QString &validDate) {
        if (validDate != m_validDate) {
            m_validDate = validDate;
            emit validDateChanged();
            qDebug() << "Valid date changed: " << validDate;
        }
    }
    QString validDate() const {
        return m_validDate;
    }

signals:
    void validDateChanged();

private:
    QString m_number;  // 身份证号码
    QString m_validDate;  // 有效日期
};

class Person : public QObject
{
    Q_OBJECT
    Q_PROPERTY(QString name2 READ getname WRITE setName NOTIFY nameChanged)
    Q_PROPERTY(IDCard* idCard READ idCard WRITE setIDCard NOTIFY idCardChanged)
public:
    explicit Person(QObject *parent = nullptr);

public:
    void setName(const QString &name) {
        if (name != m_name) {
            m_name = name;
            emit nameChanged(name);
            qDebug() << "Name changed: " << name;
        }
    }
    QString getname() const {
        return m_name;
    }

signals:
    void nameChanged(const QString &name);

private:
    QString m_name;  // 姓名

//身份证
    IDCard* idCard() const {
        return m_idCard;
    }
    void setIDCard(IDCard *idCard) {
        if (idCard != m_idCard) {
            m_idCard = idCard;
            emit idCardChanged();
            qDebug() << "ID card changed: " << idCard->number();
        }
    }

signals:
    void idCardChanged();

private:
    IDCard *m_idCard;  // 身份证

public slots:
};

#endif // PERSON_H
