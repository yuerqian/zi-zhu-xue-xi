#ifndef CHOOSEINTERFACE_H
#define CHOOSEINTERFACE_H

#include <QWidget>
#include<QDialog>
#include<QComboBox>

class chooseInterface : public QDialog
{
    Q_OBJECT
public:
    chooseInterface(QWidget *parent = nullptr);
    QComboBox* _comboBox;
    QString strSelect;//选择的ip
signals:

public slots:
    void slotComboBoxChange(QString);

};

#endif // CHOOSEINTERFACE_H
