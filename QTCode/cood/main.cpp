//应用程序抽象类
#include<QApplication>
//窗口类
#include<QWidget>
//按钮控件类
#include<QPushButton>
//对话框
#include<QLineEdit>
//布局控件
#include<QLayout>//包括了QVBoxLayout（垂直）\QHBLayout（水平）\QGridLayout(网格）
//静态控件
#include<QLabel>

int main(int argc, char* argv[])
{
    QApplication App(argc,argv);
    //构造一个窗口
    QWidget w;
    QPushButton button;
    button.setText("button text");
    button.setParent(&w);//设置窗口的父子关系，影响位置
    //设置按钮坐标,一般不用这种，一般用layout
   // button.setGeometry(100,100,500,50);
    //点击按钮响应事件，关闭程序
    //通过信号和槽响应,第一个参数发出信号的对象（QObject的子类），第二个参数触发的信号，第三个参数是发送给的对象（QObject的子类），第四个参数是发送的信号
    QObject::connect(&button,SIGNAL(clicked()),&w,SLOT(close()));

    //对话框
    QLineEdit edit;
    edit.setParent(&w);

 #if 0//通过这样注释代码,因为条件都不会进去
    //垂直布局
    //QVBoxLayout layout;
    //水平布局
    QHBoxLayout layout;
    layout.addStretch(1);//添加弹簧，防止对话框伸缩，相当于往左挤压控件，注意不同位置添加弹框效果不一样
    layout.addWidget(&button,1);//第二个参数是控件占据的比重(伸缩比例？）
    layout.addSpacing(50);//控件间隔开50像素
    layout.addWidget(&edit,1);
    layout.addStretch(1);//添加弹簧，参数是表示伸缩量（即是按一定比例分配空间），防止对话框伸缩，相当于往左挤压控件，注意不同位置添加弹框效果不一样
#endif

#if 0//注释代码
    //网格布局
    QGridLayout layout;
    layout.addWidget(&button,1,1);
    layout.addWidget(&edit,1,2);
    layout.addWidget(new QPushButton("坐标2,0"),2,1);
    layout.addWidget(new QPushButton("坐标2,1"),2,2);
    //通过弹簧将控件压在中间
    layout.setColumnStretch(3,1);//添加网格列弹簧，表示在第二列添加一个伸缩量为1的弹簧
    layout.setRowStretch(4,1);//添加网格行弹簧，表示在第二行添加一个伸缩量为1的弹簧
    layout.setColumnStretch(0,1);
    layout.setRowStretch(0,1);
    //网格合并
    layout.addWidget(new QPushButton("aaa"),3,1,1,2);//这个按钮控件占了1行2列
#endif

    /*===制作一个登陆界面布局===*/
    QGridLayout layout;
    QLineEdit* password;
    //通过弹簧将控件压在中间
    layout.setColumnStretch(3,1);//添加网格列弹簧，表示在第二列添加一个伸缩量为1的弹簧
    layout.setRowStretch(4,1);//添加网格行弹簧，表示在第二行添加一个伸缩量为1的弹簧
    layout.setColumnStretch(0,1);
    layout.setRowStretch(0,1);

    layout.addWidget(new QLabel("UserName:"),1,1);
    layout.addWidget(new QLabel("Password:"),2,1);
    layout.addWidget(new QLineEdit(),1,2);
    layout.addWidget(password=new QLineEdit(),2,2);
    password->setEchoMode(QLineEdit::Password);

    //添加嵌套布局
    QHBoxLayout* hBox;
    layout.addLayout(hBox=new QHBoxLayout,3,2);
    //在嵌套里添加布局
    hBox->addStretch(1);
    hBox->addWidget(new QPushButton("login"));

    //给窗口设置布局
    w.setLayout(&layout);

    //显示窗口
    w.show();
    //设置标题
    w.setWindowTitle("Hallo");
    return App.exec();
}
