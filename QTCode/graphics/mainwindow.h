#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

    QWidget* oldWidget;
    QWidget* widget;

    void contextMenuEvent(QContextMenuEvent *event);

private slots:
    void slottext(bool);
    void slotbtnclick();

};

#endif // MAINWINDOW_H
