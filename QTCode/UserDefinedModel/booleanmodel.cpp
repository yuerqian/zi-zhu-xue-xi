#include "booleanmodel.h"
BooleanModel::BooleanModel(QObject* parent):QAbstractItemModel(parent)
{
    rootNode=0;
}
BooleanModel::~BooleanModel()
{
    delete rootNode;
}

void BooleanModel::setRootNode(Node* node)
{
    delete rootNode;
    beginResetModel();
    rootNode=node;
    endResetModel();
}
//为当前节点（父节点）下子节点的索引数据，
//参数：row，column将要创建的子节点的索引，parent为当前节点的索引（可以找到子节点）
//1.当parent.row()，column()为-1,QModelIndex parent的void*==nullptr,即是parent.internalPointer()==nullptr时,表示根节点的子节点未创建索引，需要知道根节点下子节点，并创建索引
//通过前面创建的索引，可以找到子节点，然后再为子节点创建索引
QModelIndex BooleanModel::index(int row, int column, const QModelIndex &parent) const
{
    qDebug()<<"==========="<<__FUNCTION__<<row<<column<<parent;
    if(!rootNode||row<0||column<0)
        return QModelIndex();
    Node* parentNode=nodeFromIndex(parent);//获取根节点（parent无效时）或者父节点（有效时）
    Node* childrenNode=parentNode->children.value(row);//获得根节点的子节点或者是当前节点(父节点）的子节点
     qDebug()<<__FUNCTION__<<childrenNode->type<<childrenNode->str;
    if(!childrenNode)
        return QModelIndex();//没有子节点
    return createIndex(row,column,childrenNode);//创建节点的索引，并将节点数据放入其中，通过QModelIndex.internalPointer（）取出数据
}

Node* BooleanModel::nodeFromIndex(const QModelIndex &index) const
{
    qDebug()<<__FUNCTION__<<index;
    if(index.isValid())//已经创建索引时，取得索引的节点
    {
//        对于具有层次结构的 model来说，只有row和column值是不能确定这个元素的位置的，
//        因此，QModelIndex中除了row和 column之外，还有一个void*或者int的空白属性，可以
//        存储一个值。这个值是通过createIndex函数存入的当前节点的父节点。
        return static_cast<Node*>(index.internalPointer());//QModelIndex中的internalPointer函数返回一个void*类型的指针（这里就是节点本身的数据的父节点），返回当前节点的父节点
    }
    else//index无效时表示未创建根节点的索引，则返回根节点
    {
        return rootNode;
    }

}
// 获取父节点下子节点的行数
int BooleanModel::rowCount(const QModelIndex &parent) const//每个数据都会进入设置一下行数
{
    qDebug()<<__FUNCTION__<<parent;
    if(parent.column()>0)
        return 0;
    Node* parentNode=nodeFromIndex(parent);//有父节点则取父节点，没有则取根节点
    if(!parentNode)
        return 0;
    qDebug()<<__FUNCTION__<<parentNode->children.count();
    return parentNode->children.count();//有多少个子节点，就有多少行
}
// 获取父节点下子节点列数
int BooleanModel::columnCount(const QModelIndex &parent) const
{
    qDebug()<<__FUNCTION__<<parent;
    return 2;
}
//// 通过子节点索引获取父节点索引
QModelIndex BooleanModel::parent(const QModelIndex &child) const
{
    qDebug()<<__FUNCTION__;
    Node* node=nodeFromIndex(child);//获得当前子节点
    if(!node)
        return QModelIndex();
    Node* parentNode=node->parent;//子节点的父节点
    if(!parentNode)
        return QModelIndex();
    Node* grandparentNode=parentNode->parent;//子节点的父节点的父节点
    if(!grandparentNode)
        return QModelIndex();
    int row=grandparentNode->children.indexOf(parentNode);
    return createIndex(row,0,parentNode);

}
//注意树形结构同级子节点都是row=0开始排序
QVariant BooleanModel::data(const QModelIndex &index, int role) const
{
    qDebug()<<__FUNCTION__<<index.row();
    if(role!=Qt::DisplayRole)
        return QVariant();
    Node* node=nodeFromIndex(index);
    if(!node)
        return QVariant();
    if(index.column()==0)//第一列总是树形结构，不能改到第二列，不知道为什么
    {
        switch(node->type)
        {
        case Node::Root:
            return tr("Root");
        case Node::OrExpression:
            return tr("OrExpresion");
        case Node::AndExpression:
            return tr("AndExpresion");
        case Node::NotExpression:
            return tr("NotExpresion");
        case Node::Atom:
            return tr("Atom");
        case Node::Identifier:
            return tr("Identifier");
        case Node::Operator:
            return tr("Operator");
        case Node::Punctuator:
            return tr("Punctuator");
        }
    }else if(index.column()==1)
    {
        return node->str;
    }
    return QVariant();
}
QVariant BooleanModel::headerData(int section, Qt::Orientation orientation, int role) const
{
    qDebug()<<__FUNCTION__;
    if(orientation==Qt::Horizontal&&role==Qt::DisplayRole)
    {
        if(section==0)
        {
            return tr("Node");
        }else if(section==1)
        {
            return tr("value");
        }
    }
    return QVariant();
}







