#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QFile>
#include<QDebug>
#include<QXmlStreamReader>
#include<QXmlStreamWriter>

#include<QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QFile file("xmltxt.xml");
    if(!file.open(QIODevice::ReadOnly|QFile::Text))
    {
        qDebug()<<"open file fail!"<<file.errorString();
    }
    else
    {
        QXmlStreamReader reader(&file);
#if 0
        while(!reader.atEnd())
        {
            QXmlStreamReader::TokenType type=reader.readNext();
            //使用type如下，或者通过isStartElement等判断（比如if(reader.isStartElement()){})
            switch(type)
            {
            case QXmlStreamReader::StartDocument://开始文档获取版本，编码
                qDebug()<<"============开始文档编辑：==========="<<reader.documentVersion().toString()
                       <<"--"<<reader.documentEncoding().toString();
                break;
            case QXmlStreamReader::EndDocument:
                qDebug()<<"==============结束文档===========";
                break;
            case QXmlStreamReader::StartElement://元素项
                qDebug()<<"根元素："<<reader.name().toString()<<reader.attributes().value("sidebearings").toString();
                break;
            case QXmlStreamReader::EndElement://结束元素
                qDebug()<<"末尾元素"<<reader.name().toString();
                break;
            case QXmlStreamReader::Comment://注释
                qDebug()<<"注释："<<reader.text().toString();
                break;
            case QXmlStreamReader::Characters://内容
                qDebug()<<"内容："<<reader.text().toString();
                break;
            case QXmlStreamReader::DTD://DTD数据
                qDebug()<<"文档类型定义："<<reader.text().toString();
                break;
            case QXmlStreamReader::EntityReference://实体引用
                qDebug()<<"实体引用:"<<reader.name().toString()<<"，内容："<<reader.text().toString();
                break;
            case QXmlStreamReader::ProcessingInstruction://处理指令
                qDebug()<<"处理指令："<<reader.processingInstructionData().toString();
                break;
            case QXmlStreamReader::Invalid://发生错误
                qDebug()<<"错误："<<reader.errorString();
                break;
            case QXmlStreamReader::NoToken://没有读取到任何数据
                qDebug()<<"没有读取到任何数据！";
                break;

            }
        }
        if(reader.hasError())//错误信息
            qDebug()<<QString::fromLocal8Bit("错误信息：%1,行号:%2,列号：%3,字符位移：%4").arg(reader.errorString()).arg(reader.lineNumber()).arg(reader.columnNumber()).arg(reader.characterOffset());
#endif
#if 0
        while(reader.readNextStartElement())
        {
            qDebug()<<reader.name().toString()<<"==";
//            qDebug()<<reader.readElementText();
            if(reader.name().toString()=="page")
            {
                qDebug()<<reader.readElementText();

            }
            else
            {
//                reader.skipCurrentElement();
            }

        }
#endif
        file.close();
    }

#if 0
    QFile writeFile("file.xml");
    if(!writeFile.open(QIODevice::WriteOnly|QFile::Text))
    {
        qDebug()<<"文件打开失败！";
    }else{
        QXmlStreamWriter write(&writeFile);
        write.setCodec("utf8");//编码格式
        write.setAutoFormatting(true);//自动编码
        write.writeStartDocument("1.0",true);//开始文档
        write.writeComment(QString::fromUtf8("这是注释的内容"));//注释
        write.writeProcessingInstruction("xml-stylesheet type=\"text/css\" href=\"style.css\"");//处理指令
        write.writeDTD(QString::fromUtf8("<!DOCTYPE Blogs [ <!ENTITY Copyright \"Copyright 2016《Qt实战一二三》\"> <!ELEMENT Blogs (Blog)> <!ELEMENT Blog (作者,主页,个人说明)> <!ELEMENT 作者     (#PCDATA)> <!ELEMENT 主页     (#PCDATA)> <!ELEMENT 个人说明  (#PCDATA)> ]>"));
        write.writeStartElement("bookindex");//元素
        write.writeAttribute("version","2.0");//属性
        write.writeStartElement("entry");//元素
        write.writeAttribute("term","sidebearings");//属性
        write.writeTextElement(QString::fromUtf8("作者"), QString::fromUtf8("一去丶二三里"));//写入元素和纯文本内容
        write.writeTextElement(QString::fromUtf8("主页"), "http://blog.csdn.net/liang19890820");
        write.writeTextElement(QString::fromUtf8("个人说明"), QString::fromUtf8("青春不老，奋斗不止！"));
        write.writeEntityReference("Copyright");//实体引用
        write.writeCDATA(QString::fromUtf8("<Qt分享&&交流>368241647</Qt分享&&交流>"));
        write.writeEmptyElement(QString::fromUtf8("Empty"));  // 空元素
        write.writeEndElement();
        write.writeEndElement();

        write.writeEndDocument();

        writeFile.close();
    }
#endif

#if 0
    QDomDocument doc;
    QDomProcessingInstruction xmlProcessInstruction=doc.createProcessingInstruction("xml", "version=\"1.0\" encoding=\"UTF-8\" standalone=\"yes\"");
    QDomComment xmlComment=doc.createComment("这里是注释");
    QDomProcessingInstruction xmlstyleInstruction=doc.createProcessingInstruction("xml-stylesheet", "type=\"text/css\" href=\"style.css\"");
    doc.appendChild(xmlProcessInstruction);//开始文档（xml声明）
    doc.appendChild(xmlComment);//注释
    doc.appendChild(xmlstyleInstruction);//处理指令

    //设置根元素
    QDomElement root=doc.createElement("bookindex");
    root.setAttribute("version","1.0");//设置属性
    doc.appendChild(root);

    //创建子元素
    QDomElement child=doc.createElement("entry");
    child.setAttribute("term","sidebearings");
    root.appendChild(child);//添加子节点

    // 元素 <作者>、<主页>、<个人说明>
    QDomElement author = doc.createElement(QString::fromUtf8("作者"));
    QDomElement home = doc.createElement(QString::fromUtf8("主页"));
    QDomElement instruction = doc.createElement(QString::fromUtf8("个人说明"));
    child.appendChild(author);
    child.appendChild(home);
    child.appendChild(instruction);

    //元素添加文本数据
    QDomText textAuthor=doc.createTextNode("这是作者名称");
    QDomText textHome=doc.createTextNode("https://blog.csdn.net/liang19890820/article/list/7?");
    QDomText textInstruction=doc.createTextNode("青春不老，奋斗不止！");
    author.appendChild(textAuthor);
    home.appendChild(textHome);
    instruction.appendChild(textInstruction);

    //保存
    QFile domfile("dom.xml");
    if(domfile.open(QIODevice::WriteOnly|QFile::Text))
    {
        QTextStream out(&domfile);
        doc.save(out,QDomNode::EncodingFromDocument);//根据dom的方式写文件
        domfile.close();
    }
#endif

#if 1
    QDomDocument doc;
    QFile domReadFile("dom.xml");
    if(!domReadFile.open(QIODevice::ReadOnly|QFile::Text))
    {
        return;
    }
    if(!doc.setContent(&domReadFile))//解析xml文档
    {
        domReadFile.close();
        return;
    }
    domReadFile.close();

    QDomElement root=doc.documentElement();
    qDebug()<<root.tagName();//返回元素的名称

    //获取属性
    if(root.hasAttribute("version"))
        qDebug()<<"根节点属性："<<root.attribute("version");

    //解析根元素之上的xml声明、注释等内容
    qDebug()<<"================解析根元素之上的xml声明、注释等内容=================";
    QDomNode node=root.previousSibling();//兄弟节点
    while(!node.isNull())
    {
        switch(node.nodeType())
        {
        case QDomNode::ProcessingInstructionNode://处理指令
        {
            QDomProcessingInstruction Instruction=node.toProcessingInstruction();//获得处理指令数据
            qDebug()<<"处理指令："<<Instruction.target()<<Instruction.data();//取出数据
            if(QString::compare(Instruction.target(),"xml")==0)
            {

            }else if(QString::compare(Instruction.target(),"xml-stylesheet")){

            }
            break;
        }
        case QDomNode::CommentNode://注释
        {
            QDomComment comment=node.toComment();//获得注释数据
            qDebug()<<"注释："<<comment.data();//取出数据
            break;
        }
        default:
            break;

        }
        node=node.previousSibling();//取得上一个兄弟节点（同级节点）
    }
    qDebug()<<"================code end！=================";

    //解析xml主体部分，递归
    qDebug()<<"================解析XML主体部分=================";
    nodeNext(root);
    qDebug()<<"================code end！=================";

#endif

}

MainWindow::~MainWindow()
{
    delete ui;
}

////递归解析xml主体部分，逻辑是：当前节点有子节点（通过firstChild函数找到第一个子节点，通过nextSibling找到其他的子节点）则递归往下遍历，没有子节点则返回
void MainWindow::nodeNext(QDomElement &dom)
{
    QDomNode node=dom.firstChild();//第一个子节点
//    qDebug()<<node.nodeName()<<node.nodeType()<<node.nodeValue()<<"=============================";
    while(!node.isNull())//当前节点
    {
        switch(node.nodeType())
        {
        case QDomNode::TextNode://找出文本节点，输出文本内容
        {
            qDebug()<<"节点的文本内容："<<node.toText().data();
            break;
        }
        case QDomNode::ElementNode://找到元素节点，并且查看是否有子节点
        {
            QDomElement element=node.toElement();//当前节点转换成元素
            if(!element.isNull())
            {
                qDebug()<<"节点："<<element.tagName();
                if(element.hasChildNodes())//有子节点先遍历子节点
                {
                    nodeNext(element);//递归查找子节点
                }
                if(QString::compare(element.tagName(),"主页")==0)
                {
                    qDebug()<<"找到了<主页>节点："<<element.tagName()<<element.text();
                }
            }
            break;
        }
        default:
            break;
        }
        node=node.nextSibling();//取得下一个兄弟（同级）节点，找到其他的子节点
    }
    return;
}
