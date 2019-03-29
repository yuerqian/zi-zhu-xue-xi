#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"track.h"
#include<QTableWidget>
#include"trackdelegate.h"

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

private:
    QList<Track> list;
    QTableWidget* TableWidget;

};

#endif // MAINWINDOW_H
