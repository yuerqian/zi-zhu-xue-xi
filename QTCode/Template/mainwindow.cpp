#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QDebug>
#include<QFileDialog>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("main window");
    QAction* openAction=new QAction(QIcon(":/image/image1"),tr("&Open"),this);
    openAction->setShortcut(QKeySequence::Open);//设置快捷键方式
    openAction->setStatusTip("open an exiting file");//状态栏提醒的内容
    connect(openAction,&QAction::triggered,this,&MainWindow::open);

    QAction* saveAction=new QAction(QIcon(":/image/image1"),tr("&save..."),this);
    saveAction->setShortcut(QKeySequence::Save);
    saveAction->setStatusTip("save file");
    connect(saveAction,&QAction::triggered,this,&MainWindow::save);


    QMenu* file=ui->menuBar->addMenu(tr("File"));//添加一个菜单栏
    QMenu* edit=ui->menuBar->addMenu(tr("edit"));
    file->addAction(openAction);
    file->addAction(saveAction);
    edit->addAction(openAction);

   QToolBar* toolbar= addToolBar("&file");//添加一个工具栏
   toolbar->addAction(openAction);
   QToolBar* toolbar2= addToolBar("&file");//添加一个工具栏
   toolbar2->addAction(openAction);
   //ui->mainToolBar->addAction(openAction);

    QStatusBar* statusbar=statusBar();//返回状态栏
    m_textedit=new QTextEdit(this);
    setCentralWidget(m_textedit);
    this->setWindowModified(true);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::open()
{
#if 0
//    QMessageBox::information(this,tr("information"),tr("open"));
    QDialog* dailog=new QDialog();
    dailog->setAttribute(Qt::WA_DeleteOnClose);//关闭对话框时销毁，避免内存泄漏
    dailog->setWindowTitle("dailog");
    dailog->show();
//    dailog->exec();
//    qDebug()<<dailog->result();
//    if(dailog.exec()==QDialog::Accepted)
//    {
//        qDebug()<<"dialog is accept";
//    }
#endif
    QString path=QFileDialog::getOpenFileName(this,tr("open file"),".",tr("text file(*.txt)"));//对话框获取文件路径
    if(!path.isEmpty())
    {
        QFile file(path);
        if(!file.open(QIODevice::ReadOnly|QIODevice::Text))
        {
            QMessageBox::warning(this,"read file",tr("can not open file:\n%1").arg(path));
            return;
        }
        QTextStream in(&file);
        m_textedit->setText(in.readAll());
        file.close();
    }else{
        QMessageBox::warning(this,"read file",tr("you did not select any file"));
    }

}


void MainWindow::save()
{
    QString path=QFileDialog::getSaveFileName(this,"save file",".","text file(*.txt)");
    if(!path.isEmpty())
    {
        QFile file(path);
        if(!file.open(QIODevice::WriteOnly|QIODevice::Text))
        {
            QMessageBox::warning(this,"read file",tr("can not open file:\n%1").arg(path));
            return;
        }
        QTextStream out(&file);
        out<<m_textedit->toPlainText();
        file.close();
    }else
    {
        QMessageBox::warning(this,"read file",tr("you did not select any file"));
    }
}



