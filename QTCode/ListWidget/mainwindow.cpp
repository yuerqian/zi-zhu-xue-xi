#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->listWidget->addItem(new QListWidgetItem(QIcon("E:\\QTCode\\ListWidget\\QRCode.bmp"),tr("item1")));
    ui->listWidget->addItem("Item2");
    //ui->listWidget->setViewMode(QListView::IconMode);

    connect(ui->listWidget,SIGNAL(currentTextChanged(QString)),ui->label,SLOT(setText(QString)));

    ui->treeWidget->setColumnCount(4);
    QStringList head;
    head<<"name"<<"ege";
    ui->treeWidget->setHeaderLabels(head);
    QStringList rootlist;
    rootlist<<"li"<<"男";
    QTreeWidgetItem* root=new QTreeWidgetItem(ui->treeWidget,rootlist);
    QStringList leaf1list;
    leaf1list<<"zhang"<<"女";
    QTreeWidgetItem* leaf1=new QTreeWidgetItem(root,leaf1list);
    QTreeWidgetItem* leaf2=new QTreeWidgetItem(root,QStringList("leaf2"));
    leaf2->setCheckState(0,Qt::Unchecked);
    root->addChild(leaf2);
    QList<QTreeWidgetItem*> rootlistItem;
    rootlistItem<<root;
    ui->treeWidget->insertTopLevelItems(0,rootlistItem);
    ui->treeWidget->insertTopLevelItems(1,rootlistItem);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_listWidget_currentItemChanged(QListWidgetItem *current, QListWidgetItem *previous)
{

}
