#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QDebug>
//如果是window平台
#ifdef Q_OS_WIN
#pragma comment(lib,"user32.lib")
#include<qt_windows.h>
#endif

const ULONG_PTR CUSTOM_TYPE = 10000;
const QString c_strTitle = "ReceiveMessage";
COPYDATASTRUCT copydata;
HWND hwnd = NULL;
HWND m_sender=NULL;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowTitle("ReceiveMessage");
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_clicked()
{

    //查找窗口
        //do
        //{
           LPWSTR path = (LPWSTR)c_strTitle.utf16();  //path = L"SendMessage"
           hwnd = ::FindWindowW(NULL, path);
        //} while (hwnd == (HWND)effectiveWinId()); // 忽略自己
    //向窗口发送消息
        if (::IsWindow(hwnd))
        {
            QString filename = QStringLiteral("进程通信-Windows消息");
            QByteArray data = filename.toUtf8();


            copydata.dwData = CUSTOM_TYPE;  // 用户定义数据
            copydata.lpData = data.data();  //数据大小
            copydata.cbData = data.size();  // 指向数据的指针

            m_sender = (HWND)effectiveWinId();//获取窗口标志id

            ::SendMessage(hwnd, WM_COPYDATA, reinterpret_cast<WPARAM>(m_sender), reinterpret_cast<LPARAM>(&copydata));
        }
}

bool MainWindow::nativeEvent(const QByteArray &eventType, void *message, long *result)
{
    MSG *param = static_cast<MSG *>(message);

    switch (param->message)
    {
    case WM_COPYDATA:
    {
        qDebug()<<__FUNCTION__;
        COPYDATASTRUCT *cds = reinterpret_cast<COPYDATASTRUCT*>(param->lParam);
        if (cds->dwData == CUSTOM_TYPE)
        {
            QString strMessage = QString::fromUtf8(reinterpret_cast<char*>(cds->lpData), cds->cbData);
            QMessageBox::information(this, QStringLiteral("提示"), strMessage);
            *result = 1;
            return true;
        }
    }
    }

    return QWidget::nativeEvent(eventType, message, result);
}
