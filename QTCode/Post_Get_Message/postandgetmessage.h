#ifndef POSTANDGETMESSAGE_H
#define POSTANDGETMESSAGE_H

#include <QWidget>
#include<QNetworkReply>
#include<QNetworkRequest>
#include<QLineEdit>
#include<QPushButton>
#include<QLabel>
#include<QVBoxLayout>




class PostAndGetMessage : public QWidget
{
    Q_OBJECT
public:
    explicit PostAndGetMessage(QWidget *parent = nullptr);
    QNetworkAccessManager *m_accessManager;
    QNetworkRequest request;
    int times=0;
    QVBoxLayout* lay;
    QPushButton* button;
    QLineEdit* edit;
    QLabel *label;


    ~PostAndGetMessage();
signals:

public slots:
    void finishedSlot(QNetworkReply *reply);
    void on_pushButton_clicked();
};

#endif // POSTANDGETMESSAGE_H
