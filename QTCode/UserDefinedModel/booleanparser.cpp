#include "booleanparser.h"

BooleanParser::BooleanParser()
{

}
Node *BooleanParser::parse(const QString &expr)
{
    in = expr;
    in.replace(" ", "");
    pos = 0;

    Node *node = new Node(Node::Root);
    addChild(node, parseOrExpression());
    return node;
}
//运算优先级：非运算>与运算>或运算
//运行或运算就要先运算与运算
Node *BooleanParser::parseOrExpression()
{
    Node *childNode = parseAndExpression();
    if (matchToken("||")) {
        Node *node = new Node(Node::OrExpression);
        addChild(node, childNode);
        while (matchToken("||")) {
            addToken(node, "||", Node::Operator);
            addChild(node, parseAndExpression());
        }
        return node;
    } else {
        return childNode;
    }
}
//想运算与运算，先算非运算，
Node *BooleanParser::parseAndExpression()
{
    Node *childNode = parseNotExpression();
    if (matchToken("&&")) {
        Node *node = new Node(Node::AndExpression);
        addChild(node, childNode);
        while (matchToken("&&")) {
            addToken(node, "&&", Node::Operator);
            addChild(node, parseNotExpression());
        }
        return node;
    } else {
        return childNode;
    }
}
//非运算，直接运算，运算完后添加子节点，
Node *BooleanParser::parseNotExpression()
{
    if (matchToken("!")) {
        Node *node = new Node(Node::NotExpression);
        while (matchToken("!"))
            addToken(node, "!", Node::Operator);
        addChild(node, parseAtom());
        return node;
    } else {
        return parseAtom();
    }
}
//判断当前字符是否是括号；是括号，则添加子节点并位置下移，不是，则获取字母和数字的字符串
Node *BooleanParser::parseAtom()
{
    if (matchToken("(")) {
        Node *node = new Node(Node::Atom);
        addToken(node, "(", Node::Punctuator);
        addChild(node, parseOrExpression());
        addToken(node, ")", Node::Punctuator);
        return node;
    } else {
        return parseIdentifier();
    }
}
//截取是字母和数字的字符串
Node *BooleanParser::parseIdentifier()
{
    int startPos = pos;
    while (pos < in.length() && in[pos].isLetterOrNumber())
        ++pos;
    if (pos > startPos) {
        return new Node(Node::Identifier,
                        in.mid(startPos, pos - startPos));
    } else {
        return 0;
    }
}
//子节点节点赋值，位置不移动
void BooleanParser::addChild(Node *parent, Node *child)
{
    if (child) {
        parent->children += child;
        parent->str += child->str;
        child->parent = parent;
    }
}
//判断当前字符串是否规范，并新增对应类型的子节点，并赋值，位置移动到下一个
void BooleanParser::addToken(Node *parent, const QString &str,
                             Node::Type type)
{
    if (in.mid(pos, str.length()) == str) {
        addChild(parent, new Node(type, str));
        pos += str.length();
    }
}
//判断当前pos后面的字符串是否与当前字符串匹配
bool BooleanParser::matchToken(const QString &str) const
{
    return in.mid(pos, str.length()) == str;
}
