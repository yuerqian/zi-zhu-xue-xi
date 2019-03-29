#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QLocalServer>
#include<QList>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;

    QLocalServer* m_server;
    QList<QString> fortunes;

public slots:

    void slotSendFutunes();
};

#endif // MAINWINDOW_H
