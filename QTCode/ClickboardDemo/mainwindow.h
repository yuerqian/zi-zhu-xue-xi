#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QMouseEvent>

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

    void on_copyBtn_clicked();

    void on_pasteBtn_clicked();

private:
    Ui::MainWindow *ui;

protected:
    void mouseReleaseEvent(QMouseEvent* e);
};

#endif // MAINWINDOW_H
