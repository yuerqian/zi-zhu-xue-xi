#ifndef CONTROLS_H
#define CONTROLS_H

#include <QWidget>
#include<QTextEdit>

class Controls : public QWidget
{
    Q_OBJECT
public:
    explicit Controls(QWidget *parent = nullptr);
    QTextEdit* m_edit;

signals:

public slots:
    void SlotComboBoxIndexChage(const QString &str);

};

#endif // CONTROLS_H
