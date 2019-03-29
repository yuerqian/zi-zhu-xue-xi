#include "node.h"

Node::Node(Type type,const QString &str)
{
    this->type=type;
    this->str=str;
    this->parent=0;//父节点为0
}
Node::~Node()
{
    qDeleteAll(children);//清空内存
    children.clear();
}
