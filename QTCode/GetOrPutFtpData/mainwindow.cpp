#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QPushButton>
#include<QVBoxLayout>
#include<QDebug>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QWidget* widget=new QWidget();
    takeCentralWidget();
    setCentralWidget(widget);
    QPushButton* btn=new QPushButton("上传");
    QPushButton* btn2=new QPushButton("下载");
    m_upBar=new QProgressBar();
    m_downBar=new QProgressBar();

    QVBoxLayout* lay=new QVBoxLayout();
    lay->addWidget(btn);
    lay->addWidget(m_upBar);
    lay->addWidget(btn2);
    lay->addWidget(m_downBar);
    widget->setLayout(lay);

    connect(btn,SIGNAL(clicked(bool)),this,SLOT(slotBtnclick()));
    connect(btn2,SIGNAL(clicked(bool)),this,SLOT(download()));

}

MainWindow::~MainWindow()
{
    delete ui;
}

//上传文件
void MainWindow::slotBtnclick()
{
    qDebug()<<__FUNCTION__;
    m_Ftp.setHostPort("192.168.10.246",21);
    m_Ftp.setUserInfo("Andy","Hemei13088..");
    m_Ftp.put("E:\\02.zip","//02.zip");
    connect(&m_Ftp,SIGNAL(error(QNetworkReply::NetworkError)),this,SLOT(error(QNetworkReply::NetworkError)));
    connect(&m_Ftp, SIGNAL(uploadProgress(qint64, qint64)), this, SLOT(uploadProgress(qint64, qint64)));

}

// 下载文件
void MainWindow::download()
{
    qDebug()<<__FUNCTION__;
    m_Ftp.setHostPort("192.168.10.246",21);
    m_Ftp.setUserInfo("Andy","Hemei13088..");
    m_Ftp.get("//02.zip", "E:\\svn\\02.zip");
    connect(&m_Ftp, SIGNAL(error(QNetworkReply::NetworkError)), this, SLOT(error(QNetworkReply::NetworkError)));
    connect(&m_Ftp, SIGNAL(downloadProgress(qint64, qint64)), this, SLOT(downloadProgress(qint64, qint64)));
}

// 错误处理
void MainWindow::error(QNetworkReply::NetworkError error)
{
    qDebug()<<"==="<<error;
    switch (error) {
    case QNetworkReply::HostNotFoundError :
        qDebug() << QString::fromLocal8Bit("主机没有找到");
        break;
        // 其他错误处理
    default:
        break;
    }
}

//上传进度条
void MainWindow::uploadProgress(qint64 bytesSent, qint64 bytesTotal)
{
    m_upBar->setMaximum(bytesTotal);
    m_upBar->setValue(bytesSent);
}

//下载进度条
void MainWindow::downloadProgress(qint64 bytesReceived, qint64 bytesTotal)
{
    m_downBar->setMaximum(bytesTotal);
    m_downBar->setValue(bytesReceived);
}


