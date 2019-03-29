#include "ftpmanage.h"
#include <QFileInfo>
#include<QDebug>

FtpManager::FtpManager(QObject *parent)
    : QObject(parent)
{
    // 设置协议
    m_pUrl.setScheme("ftp");
}

// 设置地址和端口
void FtpManager::setHostPort(const QString &host, int port)
{
    m_pUrl.setHost(host);
    m_pUrl.setPort(port);
}

// 设置登录 FTP 服务器的用户名和密码
void FtpManager::setUserInfo(const QString &userName, const QString &password)
{
    m_pUrl.setUserName(userName);
    m_pUrl.setPassword(password);
}

// 上传文件
void FtpManager::put(const QString &fileName, const QString &path)
{
    QFile file(fileName);
    if(!file.open(QIODevice::ReadOnly))
        qDebug()<<"open file fail!";
    QByteArray data = file.readAll();

    m_pUrl.setPath(path);//注意此时m_url的值，很容易出错
    qDebug()<<m_pUrl.url();
//    m_manager.setNetworkAccessible(QNetworkAccessManager::Accessible);
    QNetworkReply *pReply = m_manager.put(QNetworkRequest(m_pUrl), data);


    connect(pReply, SIGNAL(uploadProgress(qint64, qint64)), this, SIGNAL(uploadProgress(qint64, qint64)));//发送更新进度条信号
    connect(pReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(error(QNetworkReply::NetworkError)));//发送错误解析的信号
}

// 下载文件
void FtpManager::get(const QString &path, const QString &fileName)
{
    QFileInfo info;
    info.setFile(fileName);

    m_file.setFileName(fileName);
    m_file.open(QIODevice::WriteOnly | QIODevice::Append);
    m_pUrl.setPath(path);//注意此时m_url的值，很容易出错
    qDebug()<<m_pUrl.url();

    QNetworkReply *pReply = m_manager.get(QNetworkRequest(m_pUrl));

    connect(pReply,SIGNAL(readyRead()),this,SLOT(readFile()));//从通道中读到新的可用数据时发送该信号，当下载的文件比较大时需要及时处理，否则会导致通道无法缓存大数据而崩溃
    connect(pReply, SIGNAL(finished()), this, SLOT(finished()));//下载结束后写文件
    connect(pReply, SIGNAL(downloadProgress(qint64, qint64)), this, SIGNAL(downloadProgress(qint64, qint64)));//发送更新进度条信号
    connect(pReply, SIGNAL(error(QNetworkReply::NetworkError)), this, SIGNAL(error(QNetworkReply::NetworkError)));//发送错误解析的信号
}

// 下载过程中通道中有准备好的数据则写文件
void FtpManager::readFile()
{
    QNetworkReply *pReply = qobject_cast<QNetworkReply *>(sender());
    switch (pReply->error()) {
    case QNetworkReply::NoError : {
        qDebug()<<"readfile";
        m_file.write(pReply->readAll());
        m_file.flush();
    }
        break;
    default:
        break;
    }

}

// 下载过程中写文件
void FtpManager::finished()
{
    QNetworkReply *pReply = qobject_cast<QNetworkReply *>(sender());
    switch (pReply->error()) {
    case QNetworkReply::NoError : {
    }
        break;
    default:
        break;
    }

    m_file.close();
    pReply->deleteLater();
}
