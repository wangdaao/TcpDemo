#include "widget.h"
#include "llstcptransclient.h"
#include <QDebug>

Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    init();
}

Widget::~Widget()
{

}

void Widget::mouseDoubleClickEvent(QMouseEvent *event)
{
    qDebug() << "send" << "===============================";
    m_clientSocket->write( "123123qwdasdasdqwe21ewads");
}

void Widget::init()
{
    m_clientSocket = new LLSTcpTransClient(this);
    m_clientSocket->bind("127.0.0.1",12341);
}
