#include "mainwindow.h"
#include<QMenuBar>
#include<QMessageBox>
#include<QFileDialog>
#include<QApplication>
static const char* greeting_string[]={QT_TRANSLATE_NOOP("FISRT","NIHAO"),QT_TRANSLATE_NOOP("FISRT","HALLO")};

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent)
{
    //注意构造函数里的tr()函数，必须要指定命名空间QObject::tr(),或者，构造的类::tr()
    QMenuBar *menuBar=new QMenuBar(this);
    QMenu *fileMenu=new QMenu(MainWindow::tr("&File"),menuBar);//添加&符号标，启动程序按下Alt键后首字母出现下划线，标志菜单或者菜单项的快捷键
    QAction *newFile=new QAction(MainWindow::tr("&New..."),fileMenu);
    fileMenu->addAction(newFile);
    QAction *openFile= new QAction(QObject::tr("&Open..."), fileMenu);
    fileMenu->addAction(openFile);
    menuBar->addMenu(fileMenu);
    setMenuBar(menuBar);

    connect(openFile,SIGNAL(triggered()),this,SLOT(fileOpen()));
}


void MainWindow::fileOpen()
{
    QFileDialog *fileDialog=new QFileDialog(this);
    fileDialog->setWindowTitle(tr("Open File"));
    fileDialog->setDirectory(".");
    if(fileDialog->exec() == QDialog::Accepted)
    {
        QString path=fileDialog->selectedFiles()[0];
        QMessageBox::information(NULL,tr("Path"),tr("You　 selected\n%1").arg(path));
    }
    else
    {
        QMessageBox::information(NULL,tr("Path"),tr("You　didn't　select　any　 files."));
     }
    static const char* greeting_strings[]={QT_TRANSLATE_NOOP("FriendlyConversation","Hello"),QT_TRANSLATE_NOOP("FriendlyConversation", "Goodbye")};
    QMessageBox::information(NULL,tr("ffff"),QApplication::translate("FriendlyConversation",greeting_string[0]));
}
