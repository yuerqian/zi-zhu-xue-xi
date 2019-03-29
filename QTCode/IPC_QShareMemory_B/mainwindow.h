#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QSharedMemory>


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_loadFromMemory_clicked();

private:
    Ui::MainWindow *ui;

    QSharedMemory* m_shareMemory;
};

#endif // MAINWINDOW_H
