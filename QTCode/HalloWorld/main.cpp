//应用程序抽象类
#include<QApplication>
//窗口类
#include<QWidget>
//按钮控件类
#include<QPushButton>

int main(int argc, char* argv[])
{
    QApplication App(argc,argv);
    //构造一个窗口
    QWidget w;
    QPushButton button;
    button.setText("button text");
    button.setParent(&w);//设置窗口的父子关系，影响位置
    //点击按钮响应事件，关闭程序
    //通过信号和槽响应,第一个参数发出信号的对象（QObject的子类），第二个参数触发的信号，第三个参数是发送给的对象（QObject的子类），第四个参数是发送的信号
    QObject::connect(&button,SIGNAL(clicked()),&w,SLOT(close()));


    //显示窗口
    w.show();
    //设置标题
    w.setWindowTitle("Hallo");
    return App.exec();
}
