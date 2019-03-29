#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include<QDirModel>
#include<QTreeView>

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
    QDirModel* model;
    QTreeView* treeView;
    QModelIndex m_index;

private slots:
    void slotHeaderClicked(int index);

    void slotCreateDirectory();
    void stotRemoveDirectory();

};

#endif // MAINWINDOW_H
