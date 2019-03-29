#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QClipboard>
#include<QMessageBox>
#include<QMimeData>
#include<QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_copyBtn_clicked()
{
    QClipboard* board=QApplication::clipboard();
    board->setText("hallo world!");
}

void MainWindow::on_pasteBtn_clicked()
{
    QClipboard* board=QApplication::clipboard();
    QString str=board->text();
    QMessageBox::information(this,"nihao",str);


    //board->setMimeData(a);
    //board->mimeData()->data("text/csv");
}

void MainWindow::mouseReleaseEvent(QMouseEvent* e)
{
    QClipboard* board=QApplication::clipboard();
    qDebug()<<"======"<<board->supportsSelection();
    if(e->button()==Qt::MidButton&&board->supportsSelection())
    {
        QString str=board->text(QClipboard::Selection);
        QMessageBox::information(this,"nihao",str);
    }
}
