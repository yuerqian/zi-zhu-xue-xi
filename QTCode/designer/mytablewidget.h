#ifndef MYTABLEWIDGET_H
#define MYTABLEWIDGET_H
#include<QTableWidget>
#include<QMouseEvent>

class MyTableWidget : public QTableWidget
{
    Q_OBJECT
public:
    MyTableWidget(QWidget* parent);

protected:
    void mousePressEvent(QMouseEvent* e);
    void mouseMoveEvent(QMouseEvent* e);
    void dragEnterEvent(QDragEnterEvent* e);//发起拖放操作
    void dragMoveEvent(QDragMoveEvent* e);
    void dropEvent(QDropEvent* e);//接收拖放数据

private:
    void performDrag();//拖放类构造，开始
    QPoint startPoint;//拖放的起始位置

    QString toHtml(const QString &strBuf);
    QString toCsv(const QString& strBuf);
};

#endif // MYTABLEWIDGET_H
