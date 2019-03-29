#ifndef NODE_H
#define NODE_H
#include<QtCore>

class Node
{
public:
    enum Type
    {
        Root,//根节点
        OrExpression,//或运算
        AndExpression,//与运算
        NotExpression,//非运算
        Atom,//括号运算
        Identifier,//数字和字符的字符串
        Operator,//运算符
        Punctuator,//标点符号，比如括号
    };
public:
    Node(Type type,const QString &str="");
    Type type;//数据类型
    QString str;//数据的值
    Node* parent;//父节点
    QList<Node*> children;//子节点


    ~Node();
};

#endif // NODE_H
