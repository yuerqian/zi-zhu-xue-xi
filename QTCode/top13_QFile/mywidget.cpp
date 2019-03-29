#include "mywidget.h"
#include<QIODevice>//qt输入输出流
#include<QFile>//文件操作
#include<QApplication>
#include<QMessageBox>
#include<QDebug>
#include<QBuffer>
#include<QLabel>
#include "tcpclient.h"
#include "tcpserver.h"
#include "udpsever.h"
#include "udpclient.h"

/*QFile:硬盘上的文件
 * QBuffer:内存上的文件,有点像内存共享
 * QTcpSocket
 * QUdpSocket
 *
 * QDataString：IO流，比较适合永久化数据的存取
 * QTextString：IO流,比较适合永久化数据的存取
 */
Mywidget::Mywidget(QWidget *parent) : QWidget(parent)
{
#if 0
    //QFile:
    QFile file("../Mytest.txt");//指定文件路径，不一定需要打开文件，可以查看文件是否存在file.exists();
    file.open(QIODevice::ReadWrite);//打开文件
    file.write("bbbb");
    //file.seek();//偏移量
    file.close();
#endif

#if 0
    //QByteArray与QString
    //qt默认是UTF-8编码，QString的长度是字符个数，而不是字节个数，QByteArray的长度是字节个数，所以我们在传递字符串时一般使用QByteArray，QString是内部用的，QByteArray是用来给外部交互用，一般不建议使用char*,建议使用QByteArray
    QByteArray bu("中");
    QString ni("中");//
    qDebug()<<bu.size()<<"  "<<ni.size();
#endif

#if 0
    //QBuffer:
    QBuffer buffer;
    buffer.open(QIODevice::ReadWrite);
    buffer.write("aaa");
    buffer.write("bbbb");
    buffer.close();
    //获取内存上的内容
    qDebug()<<buffer.buffer();

    //图片保存到内存上pixmap.save(&buffer2,"PNG");，
    QBuffer buffer2;
    buffer2.open(QIODevice::ReadWrite);
    QPixmap pixmap("../aaa.png");
    pixmap.save(&buffer2,"PNG");//将文件保存到IO设备中(保存到内存上）,第二个参数是保存图片格式
    buffer2.close();

    qDebug()<<"图片内存"<<buffer2.buffer().size();

    //从内存上下载图片pixmap2.loadFromData(buffer2.buffer(),"PNG");
    QPixmap pixmap2;
    pixmap2.loadFromData(buffer2.buffer(),"PNG");
    QLabel* label=new QLabel(this);
    label->setPixmap(pixmap2);
#endif

#if 0
    //QTextStream:侧重于向QIODevice文本读写，方便输出，一般用来输出给别人方便看到的东西
    QFile file("../teststream.txt");
    file.open(QIODevice::ReadWrite);

    QTextStream textString(&file);

    textString<<1<<"aaa"<<1.2;//输出，可以将各种类型的数据转换为字符串类型输出(有一部分类型没有重写，不能够转换为字符串，比如QPoint)，但是不方便读入数据，可以用QDataString

    file.close();
#endif

#if 0
    //QDataStream:写入，侧重于数据格式和类型，输出不同数据类型，不适合给别人看
    QFile file("../datastream.txt");
    file.open(QIODevice::ReadWrite);

    QDataStream dataString(&file);

    dataString<<1<<"aaa"<<1.2<<QString("abc")<<QPoint(1,1);//输出不同类型数据可能出现乱码，QDataStream

    file.close();


#endif

#if 0
    //QTextStream:读取：侧重于数据格式和类型，可以方便的读取到不同的数据类型，这样就不用考虑（类型转换）
    QFile file("../datastream.txt");
    file.open(QIODevice::ReadWrite);

    QDataStream dataString(&file);
    int i;
    char* buf;
    double d;
    QString str;
    QPoint pt;
    dataString>>i>>buf>>d>>str>>pt;//可以方便的读取(识别)到不同的数据类型
    qDebug()<<i<<buf<<d<<str<<pt;

    file.close();
    delete[] buf;
#endif

    #if 0
    //QFile.map()虚拟内存=内存映射，在MFC中是CreateFileMapping
    QFile file("../map.data");//硬盘上文件，用来映射到内存上
    file.open(QIODevice::ReadWrite);
    qDebug()<<"===="<<file.size();//创建文件时空间大小为0
    file.write("1");
//    QByteArray aa="";
//    for(int i=1;i<(4*1024+1);i++)
//    {
//       aa=aa+i;
//    }
//    file.write(aa);

    file.resize(5*1024);//设置文件大小
    //new的时候申请到的空间与map时映射空间不一样。new时申请的空间就这么多。但是map时需要创建红黑树，映射相关等其他动作，所需要的空间比申请的空间要多，因此map申请会比new申请的空间要多。
    uchar* ptr=file.map(0,file.size());//map的大小必须和文件的大小一致,申请的空间比实际大小要大，注意内存越界问题，注意文件的大小如果为0则没有操作的内存，必须new新的内存才能操作
    //读取内存空间的值
    char* a=(char*)ptr;
    qDebug()<<"----"<<a;

    qDebug()<<"----"<<file.size();//映射不会改变文件（硬盘）空间大小
    //ptr=new uchar[100];//拓宽的是内存的控件，与硬盘大小不变
    *ptr='a';
    for(int i=1;i<(5*1024+1);i++)
        ptr[i]='c';
    //qDebug()<<"===="<<(char*)ptr;
    qDebug()<<file.size();

    file.unmap(ptr);
    file.close();
#endif


}
int main(int argc,char* argv[])
{
    QApplication app(argc,argv);
//    Mywidget w;
//    w.show();
#if 0
    TcpServer s;s.show();
    TcpClient c;c.show();
    s.setWindowTitle("TcpServer");
    c.setWindowTitle("TcpClient");
#endif
    UdpSever udps;udps.show();
    UdpClient udpc;udpc.show();
    udps.setWindowTitle("udpServer");
    udpc.setWindowTitle("UdpClient");

    return app.exec();
}
