#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QGridLayout>
#include<QHBoxLayout>
#include<QDebug>
#include<QDir>
#include<QPushButton>
#include<QInputDialog>
#include<QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    model=new QDirModel(this);
    model->setReadOnly(false);
    model->setSorting(QDir::DirsFirst|QDir::IgnoreCase|QDir::Name);//排序

    treeView=new QTreeView(this);
    treeView->setModel(model);
    treeView->header()->setStretchLastSection(true);
    treeView->header()->setSortIndicator(0,Qt::AscendingOrder);
    //    treeView->header()->setSortIndicatorShown(true);
    //    treeView->header()->setEnabled(true);
    treeView->setSortingEnabled(true);
    //    connect(treeView->header(), SIGNAL(sectionPressed(int)), this, SLOT(slotHeaderClicked(int)));

    QString str=QDir::currentPath();
    m_index=model->index(str);//找到路径对应的索引内容
    qDebug()<<m_index<<"=="<<QDir::currentPath();
    treeView->expand(m_index);//展开索引内容对应的路径
    treeView->scrollTo(m_index);//滚动到对应的索引内容
    treeView->resizeColumnToContents(0);

    QPushButton* createBtn=new QPushButton("Create Derectory..");
    QPushButton* delBtn=new QPushButton("Remove");
    QHBoxLayout* layH=new QHBoxLayout(this);
    layH->addWidget(createBtn);
    layH->addWidget(delBtn);
    connect(createBtn,SIGNAL(clicked(bool)),this,SLOT(slotCreateDirectory()));
    connect(delBtn,SIGNAL(clicked(bool)),this,SLOT(stotRemoveDirectory()));

    QGridLayout* lay=new QGridLayout(this);
    lay->addWidget(treeView,0,0);
    lay->addLayout(layH,1,0);
    ui->centralWidget->setLayout(lay);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::slotHeaderClicked(int index)
{
    qDebug()<<index;
    //    treeView->header()->setEnabled(false);
    if (index != 1)
    {
        //不是我们想要的那一列
        treeView->header()->setSortIndicatorShown(false);
        //        treeView->setSortingEnabled(false);
        //        treeView->header()->setEnabled(true);
        return;
    }
    treeView->header()->setSortIndicatorShown(true);
    //    treeView->header()->setSortIndicator(1,Qt::AscendingOrder);
    treeView->setSortingEnabled(true);

}

void MainWindow::slotCreateDirectory()
{

    //获取当前目录 模型索引
    QModelIndex index = treeView->currentIndex();
    if (!index.isValid())
        return;
    //获取创建目录名
    QString dirName = QInputDialog::getText(this,tr("Create Directory"),tr("Directory name"));
    //创建子目录 mkdir(模型索引，目录名)
    if (!dirName.isEmpty()) {
        if (!model->mkdir(index, dirName).isValid())
            QMessageBox::information(this, tr("Create Directory"),tr("Failed to create the directory"));
    }


}

void MainWindow::stotRemoveDirectory()
{

    QModelIndex index = treeView->currentIndex();
    if (!index.isValid())
        return;

    //删除目录 rmdir(模型索引)
    bool ok;
    if (model->fileInfo(index).isDir()) {
        ok = model->rmdir(index);
    } else {
        ok = model->remove(index);
    }
    if (!ok)
        QMessageBox::information(this, tr("Remove"),tr("Failed to remove %1").arg(model->fileName(index)));


}
