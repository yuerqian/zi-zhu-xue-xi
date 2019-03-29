#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include"ftpmanage.h"
#include<QProgressBar>

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
    FtpManager m_Ftp;
    QProgressBar* m_upBar;//上传进度条
    QProgressBar* m_downBar;//下载进度条

public slots:
    void slotBtnclick();//上传文件
    void download();//下载文件
    void error(QNetworkReply::NetworkError error);//接收错误信号
    void uploadProgress(qint64, qint64);//下载季度条更新
    void downloadProgress(qint64, qint64);//下载季度条更新

};

#endif // MAINWINDOW_H
