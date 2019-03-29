//应用程序抽象类
#include<QApplication>
//窗口类
#include<QWidget>
//按钮控件类
#include<QPushButton>
//输入框
#include<QLineEdit>

#include<QCompleter>

int main(int argc, char* argv[])
{
    QApplication App(argc,argv);
    //构造一个窗口
    QWidget w;

    QLineEdit edit;
    edit.show();
    edit.setParent(&w);
    //输入密码,设置文本框类型
  //  edit.setEchoMode(QLineEdit::Password);
    //获取输入框数据
    QString text= edit.text();
    //输入提示
    edit.setPlaceholderText("请输入");
    //输入框输入智能提示-start
    QCompleter completer(QStringList()<<"aaa"<<"123"<<"998");
    //设置比配的模式，可以更智能找到对应提示内容
    completer.setFilterMode(Qt::MatchContains);
    edit.setCompleter(&completer);
    //-end


    //显示窗口
    w.show();
    //设置标题
    w.setWindowTitle("Hallo");
    return App.exec();
}
