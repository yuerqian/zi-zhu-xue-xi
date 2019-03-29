#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QDebug>
#include<QSqlDatabase>
#include<QSqlQuery>
#include<QSqlError>
#include<QSqlTableModel>
#include<QSqlRecord>
#include<QTableView>
#include<QGridLayout>
#include<QCompleter>
#include<QSqlRelationalTableModel>
#include<QSqlQueryModel>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    qDebug()<<QSqlDatabase::drivers();
    QSqlDatabase db=QSqlDatabase::addDatabase("QSQLITE","first");//添加数据库，第一个参数可以是驱动或者是字符串，第二个参数是连接名（如果创建的连接已存在，则之前存在的会被替换掉，用不同的名称则可以连接多个数据库）
    db.setDatabaseName("E:/QTCode/Database/TCR.db3");
    if(db.open())
        qDebug()<<"database is open success";

    if(db.isOpen())
        qDebug()<<"database is open isOpen";
    QSqlQuery querySQL(db);
#if 0
    querySQL.prepare("insert into param_bankarea(gafeecod,provcod,gargnnam) values(?,?,?)");//这种ODBC风格，优点是：可以赋多个值给同一个问号；缺点是必须按问号的顺序逐个输入
    QVariantList param1;
    QVariantList param2;
    QVariantList param3;
    param1<<1111<<98<<9999;
    querySQL.addBindValue(param1);
    param2<<99<<88<<77;
    querySQL.addBindValue(param2);
    param3<<"dada"<<"dada"<<"9999";
    querySQL.addBindValue(param3);
    if(!querySQL.execBatch())
        qDebug()<<querySQL.lastError();

    qDebug()<<querySQL.executedQuery();
#endif

#if 0
    querySQL.prepare("insert into param_bankarea(gafeecod,provcod,gargnnam) values(:one,:two,:three)");
    querySQL.bindValue(":one",87);
    querySQL.bindValue(":two",89);
    querySQL.bindValue(":three","three");

    if(!querySQL.exec())
        qDebug()<<querySQL.lastError();
#endif

#if 0
    QSqlTableModel* model=new QSqlTableModel(this,db);
    QWidget* widget=new QWidget();
    QGridLayout* lay=new QGridLayout();
    QTableView* TableView=new QTableView();
    model->setTable("param_bankarea");
    model->setEditStrategy(QSqlTableModel::OnManualSubmit);
    model->setFilter("gargnnam='dada'");
//    model->select();
    if(model->select())
    {
        for(int i=0;i<model->rowCount();i++)
        {
            QSqlRecord record=model->record(i);
            for(int j=0;j<record.count();j++)
            {
                qDebug()<<record.value(j);
                record.setValue();
            }
            qDebug()<<"gargnnam:"<<record.value("gargnnam").toString();
        }
    }

    TableView->setModel(model);
    lay->addWidget(TableView);
    widget->setLayout(lay);
    setCentralWidget(widget);
#endif
//    querySQL.exec("PRAGMA foreign_keys = ON");
    querySQL.prepare("insert into student(name,age,address) values(:one,:two,:three)");
    querySQL.bindValue(":one","tom");
    querySQL.bindValue(":two",89);
    querySQL.bindValue(":three",2);

    if(!querySQL.exec())
        qDebug()<<querySQL.lastError();

    QSqlRelationalTableModel* model=new QSqlRelationalTableModel(this,db);
    QWidget* widget=new QWidget();
    QGridLayout* lay=new QGridLayout();
    QTableView* TableView=new QTableView();
    model->setTable("student");
    model->setRelation(3,QSqlRelation("city","id","name"));
    TableView->setModel(model);
    model->select();
    lay->addWidget(TableView);
    widget->setLayout(lay);
    takeCentralWidget();
    setCentralWidget(widget);
//    db.close();
//    db.removeDatabase("first");
}

MainWindow::~MainWindow()
{
    delete ui;
}
