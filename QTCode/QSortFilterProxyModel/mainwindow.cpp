#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QLineEdit>
#include<QLabel>
#include<QHBoxLayout>
#include<QVBoxLayout>
#include<QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    model=new QStringListModel(QColor::colorNames(),this);
    FilterModel=new QSortFilterProxyModel(this);
    FilterModel->setSourceModel(model);//将model过滤
    FilterModel->setFilterKeyColumn(0);

    listView=new QListView(this);
    listView->setModel(FilterModel);//过滤后的FilterModel
    QLineEdit* edit=new QLineEdit(this);
    QLabel* label=new QLabel(tr("输入正则表达式："));
    QHBoxLayout* layH=new QHBoxLayout(this);
    layH->addWidget(label);
    layH->addWidget(edit);

    comboBox=new QComboBox(this);
    comboBox->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Preferred);
    comboBox->addItem(tr("Regular expresion"),QRegExp::RegExp);
    comboBox->addItem(tr("wildcard"),QRegExp::Wildcard);
    comboBox->addItem(tr("fixed string"),QRegExp::FixedString);

    QLabel* label2=new QLabel(tr("正则表达式的模式："));
    QHBoxLayout* layH2=new QHBoxLayout(this);
    layH2->addWidget(label2);
    layH2->addWidget(comboBox);

    QVBoxLayout* layoutV=new QVBoxLayout(this);
    layoutV->addWidget(listView);
    layoutV->addLayout(layH);
    layoutV->addLayout(layH2);
    ui->centralWidget->setLayout(layoutV);

    connect(edit,SIGNAL(textChanged(QString)),this,SLOT(slotFilterChange(QString)));


}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::slotFilterChange(QString text)
{
    qDebug()<<comboBox->currentIndex()<<"=="<<comboBox->itemData(comboBox->currentIndex());
    QRegExp::PatternSyntax syntax=QRegExp::PatternSyntax(comboBox->itemData(comboBox->currentIndex()).toInt());
    QRegExp regExp(text, Qt::CaseInsensitive, syntax);
    FilterModel->setFilterRegExp(regExp);
}
