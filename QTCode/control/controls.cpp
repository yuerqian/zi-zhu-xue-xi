#include "controls.h"
//封装的应用程序类
#include<QApplication>

//控件
#include<QLabel>//静态
#include<QPushButton>//按钮
#include<QLineEdit>//对话框
#include<QComboBox>//下拉框
#include<QCheckBox>//可以打钩的选择控件
#include<QRadioButton>//单选框
#include<QTextEdit>//多行文本框，可以显示图片
#include<QTextBrowser>//只读的多行文本框
#include<QGroupBox>//外面一个线框包含多个控件，用来分组
#include<qslider.h>//模拟方式显示数值
#include<QSpinBox>//数字
#include<QDateEdit>//日期输入框
#include<QTimeEdit>//时间输入框
#include<QDateTimeEdit>//日期时间输入框
#include<QLCDNumber>//显示一些电子手表一样的数字

#include<QCompleter>

#include<QVBoxLayout>
#include<QLayout>
#include<QDebug>
#include<iostream>
using namespace std;

Controls::Controls(QWidget *parent) : QWidget(parent)
{
    QVBoxLayout* lay=new QVBoxLayout(this);//这样子可以省略给窗口设置布局this->setLayout();

    QLabel* label;
    QComboBox* combo;
    QPushButton* button;
    QRadioButton* radiobutton;
    QTextEdit* edit;
    QGroupBox* group;
    QSlider* slider;
    QSpinBox* spinbox;
    //静态文本
    lay->addWidget(label=new QLabel("<a href=www.baidu.com>baidu</a>"));//支持HTML格式
    //通过信号知道可以响应哪些消息
    //connect(label,SIGNAL(linkActivated(QString)),this,SLOT(.....));//这种方法需要写槽函数，烦！
    connect(label,&QLabel::linkActivated,[](QString str){qDebug()<<str;});//要在.pro添加CONFIG+=C++11,使用Lambda表达式
    label->setPixmap(QPixmap("../aaa.png"));//label添加图片

    //按钮
    lay->addWidget(button=new QPushButton("button"));
    button->setStyleSheet("QPushButton {font:bold 16px;color:red}");//使用ccs格式改变样式

    //单选
    lay->addWidget(radiobutton=new QRadioButton("radiobutton"));
    radiobutton->setStyleSheet("QRadioButton {font:bold 16px;color:red}");//使用ccs格式改变样式
    connect(radiobutton,&QRadioButton::clicked,[](bool isclick){qDebug()<<isclick;});//判断是否已经选中

    //多选
    lay->addWidget(new QCheckBox("check box"));


    //下拉框
    lay->addWidget(combo=new QComboBox());
    combo->addItem("select item1");
    combo->addItem("select itme2");
    combo->setEditable(true);//设置下拉框可以编辑
    QCompleter* completer;
    combo->setCompleter(completer=new QCompleter(combo->model()));//添加智能提示，这是只有输入的内容与下列框前面部分内容相同时才会显示出来
    completer->setFilterMode(Qt::MatchContains);//设置智能提示模式，使得输入的内容只要有任何与下拉框内容相同的部分都会显示出来
    connect(combo,SIGNAL(currentIndexChanged(QString)),this,SLOT(SlotComboBoxIndexChage(QString)));//因为有重载，不能使用Lambda表达式

    //多行文本框，可以用来制作报表,图片
    lay->addWidget(edit=new QTextEdit);
    edit->setText("<table border=1><tr><th>head1</th><th>head2</th></tr>"
                  "<tr><td>value1</td><td>value2</td></tr>"
                  "<tr><td>value3</td><td>value4</td></tr>"
                  "</table><br>"
                  "<img src=../aaa.png></img>");//换行需要的数据也需要双引号（“”）,border=1添加边框
    m_edit=edit;
    connect(edit,&QTextEdit::textChanged,[&](){
        qDebug()<<m_edit->toPlainText();
    });//这里不可以直接使用edit变量，而是使用类的成员（m_edit)，因为edit是局部变量，信号的槽函数不可以直接调用构造函数里的变量,在main函数里则可以（因为main函数里的变量声明周期还未结束）
    //设置滚动条
    edit->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);//在需要时显示滚动条
    edit->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);//不显示滚动条


    //合并控件，分组，可以容纳更多的控件，在里面添加一个布局
    lay->addWidget(group=new QGroupBox("kongjian"));
    QHBoxLayout* hboxlay;
    group->setLayout(hboxlay=new QHBoxLayout);//设置一个新的布局
    hboxlay->addWidget(new QPushButton("你好"));
    hboxlay->addWidget(new QPushButton("aaaadfss"));


    lay->addWidget(slider=new QSlider(Qt::Horizontal));//将控件横着放置
    slider->setMaximum(100);
    slider->setMinimum(0);

    //
    lay->addWidget(spinbox=new QSpinBox);//QSpinBox与QSlider使用一样的函数
    spinbox->setMaximum(100);
    spinbox->setMinimum(0);
    //QSpinBox与QSlider相互关联，当一个改变是另一个也改变
    connect(slider,SIGNAL(valueChanged(int)),spinbox,SLOT(setValue(int)));
    connect(spinbox,SIGNAL(valueChanged(int)),slider,SLOT(setValue(int)));


    lay->addWidget(new QDateTimeEdit);

    //显示特殊数字的控件，比如楼梯显示的数字
    QLCDNumber* lcd;
    lay->addWidget(lcd=new QLCDNumber(10));//参数10，表示可以容纳多少个数字
    lcd->display("123456");//显示各种类型数字
    lcd->setMode(QLCDNumber::Hex);//设置各种进制

}


void Controls::SlotComboBoxIndexChage(const QString &str)
{
    qDebug()<<"SlotComboBoxIndexChage触发"<<str;

}

int main(int argc,char** argv)
{
    QApplication app(argc,argv);

    Controls w;


//    QVBoxLayout* lay=new QVBoxLayout();
//    QTextEdit* edit;
//    //多行文本框，可以用来制作报表,图片
//    lay->addWidget(edit=new QTextEdit);
//    edit->setParent(&w);
//    edit->setText("<table border=1><tr><th>head1</th><th>head2</th></tr>"
//                  "<tr><td>value1</td><td>value2</td></tr>"
//                  "<tr><td>value3</td><td>value4</td></tr>"
//                  "</table><br>"
//                  "<img src=../aaa.png></img>");//换行需要的数据也需要双引号（“”）,border=1添加边框
//    QObject::connect(edit,&QTextEdit::textChanged,[&](){
//        qDebug()<<edit->toPlainText();
//    });//这里不可以直接使用edit变量，而是使用类的成员（m_edit)，因为edit是局部变量，信号的槽函数不可以直接调用构造函数里的变量
//    w.setLayout(lay);

    w.show();


    return app.exec();

}
