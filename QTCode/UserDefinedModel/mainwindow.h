#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<currencymodel.h>
#include"booleanmodel.h"
#include"booleanparser.h"
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
    CurrencyModel* model;
    BooleanModel* booleanmodel;
private slots:
   void slotBtnClicked();
   void booleanExpressionChanged(const QString &);
};

#endif // MAINWINDOW_H
