#include "mainwindow.h"
#include "ui_mainwindow.h"

#include<QTableView>
#include<QVBoxLayout>
#include<QWidget>
#include<QPushButton>
#include<QTreeView>
#include<QLabel>
#include<QLineEdit>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QWidget* widget=new QWidget();//这里不能加this
    this->setCentralWidget(widget);
#if 0
    QMap<QString,double> data;
    data["NOK"]=1.0000;
    data["NZD"]=0.2254;
    data["SEK"]=1.1991;
    data["SGD"]=0.2592;
    data["USD"]=0.1534;
    model=new CurrencyModel(this);
    model->SetCurrencyMap(data);
    QTableView* view=new QTableView(this);
    view->setModel(model);
    QPushButton* btn=new QPushButton("nihao");
    connect(btn,SIGNAL(clicked(bool)),this,SLOT(slotBtnClicked()));
    QVBoxLayout* lay=new QVBoxLayout();//这里不能加this
    lay->addWidget(view);
    lay->addWidget(btn);
    widget->setLayout(lay);
#endif
    QLabel* label=new QLabel("布尔运算");
    QLineEdit* lineEdit=new QLineEdit(this);

    booleanmodel=new BooleanModel(this);
    BooleanParser parser;
    Node *rootNode = parser.parse("!a||b");
    booleanmodel->setRootNode(rootNode);

    QTreeView* view=new QTreeView(this);
    view->setModel(booleanmodel);
    QModelIndex index=view->currentIndex();
    view->expand(index);

    connect(lineEdit,SIGNAL(textChanged(QString)),this,SLOT(booleanExpressionChanged(QString)));
    QVBoxLayout* lay=new QVBoxLayout();//这里不能加this
    lay->addWidget((label));
    lay->addWidget(lineEdit);
    lay->addWidget(view);
    widget->setLayout(lay);



//    ui->centralWidget->setLayout(lay);
//    ui->centralWidget->layout()->addWidget(view);
}

MainWindow::~MainWindow()
{
    delete ui;
}
void MainWindow::slotBtnClicked()
{
    QMap<QString,double> data;
    data["NOK"]=1.0000;
    data["NZD"]=0.2254;
    data["SEK"]=1.1991;
    data["SGD"]=0.2592;
    data["USD"]=0.1534;
    model->SetCurrencyMap(data);
}

void MainWindow::booleanExpressionChanged(const QString &text)
{
    BooleanParser parser;
    Node *rootNode = parser.parse(text);
    booleanmodel->setRootNode(rootNode);
}
