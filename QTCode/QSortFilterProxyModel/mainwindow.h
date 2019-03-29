#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QStringListModel>
#include<QListView>
#include<QSortFilterProxyModel>
#include<QComboBox>

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
    QListView* listView;
    QStringListModel* model;
    QSortFilterProxyModel* FilterModel;
    QComboBox* comboBox;

private slots:
    void slotFilterChange(QString text);

};

#endif // MAINWINDOW_H
