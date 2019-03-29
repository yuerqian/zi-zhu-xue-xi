#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QTextCodec>
#include<QMessageBox>
#include<mytablewidget.h>



MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->textEdit->setAcceptDrops(false);//关闭拖放中的放下接收效果，本身QTextEdit控件可以接收文本的路径和名称，不是内容
    setAcceptDrops(true);//打开MainWindow类拖放放下接收效果
    ui->listWidget->addItems(QStringList()<<"aa"<<"bb"<<"cc");
    ui->tableWidget->setItem(0,0,new QTableWidgetItem("one"));
    ui->tableWidget->setItem(1,0,new QTableWidgetItem("two"));
    ui->tableWidget->setItem(2,0,new QTableWidgetItem("tree"));
    ui->tableWidget_2->setItem(0,0,new QTableWidgetItem("one"));
    ui->tableWidget_2->setItem(1,0,new QTableWidgetItem("two"));
    ui->tableWidget_2->setItem(2,0,new QTableWidgetItem("tree"));
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("GB2312"));//GB2312

}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if(e->mimeData()->hasFormat("text/uri-list"))//判断是否可以拖放进来，。参数MIME类型为 text/uri-list 通常用来描述一个 URI 的列表。这些 URI 可以是文件名，可以是 URL或者其他的资源描述符。
    {
       e->acceptProposedAction();//表示执行默认拖放操作，如移动，复制，链接
    }
}
void MainWindow::dropEvent(QDropEvent *e)
{
    QList<QUrl> urls=e->mimeData()->urls();//可能多个文件拖放，就有多个路径
    if(urls.isEmpty())
        return;

    QString firstName=urls.first().toLocalFile();//取出第一个文件
    if(firstName.isEmpty())
        return;

    readFile(firstName);//读取文件内容


}
void MainWindow::readFile(QString fileName)
{
    QFile file(fileName);
    QByteArray fileContent;
    if(file.open(QIODevice::ReadOnly))
    {
        fileContent=file.readAll();
        QString temp=QString::fromLocal8Bit(fileContent);
        ui->textEdit->setText(temp);
    }

}
