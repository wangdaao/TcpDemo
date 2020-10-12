#include "llstcptransclient.h"
#include <QTcpSocket>
#include <QHostAddress>
LLSTcpTransClient::LLSTcpTransClient(QObject *paernt)
{
    init();
}

void LLSTcpTransClient::bind(QVariant ip, QVariant port)
{
    m_pClient->connectToHost(QHostAddress(ip.toString()),port.toInt());
    connect(m_pClient,&QTcpSocket::readyRead,this,&LLSTcpTransClient::onReadData);
}

void LLSTcpTransClient::write(LocalMeaasg &message)
{
    TcpMessage tcpMsg;
    MeaasgeFromLocalToTcp(message,tcpMsg);

    QByteArray array;
    array.resize(tcpMsg.head.size);

    memcpy(array.data(),&tcpMsg,tcpMsg.head.size);
    m_pClient->write(array);
}

void LLSTcpTransClient::write(QString msg)
{
    QByteArray array = msg.toUtf8();
    TcpMessage message;
    message.head.type = type_Meaasge;
    message.head.size = MessageHeadSize + array.size();
    memcpy(message.str,array.data(),array.size());

    QByteArray sendData;
    sendData.resize(message.head.size);
    memcpy(sendData.data(),&message,message.head.size);

    m_pClient->write(sendData);
}

void LLSTcpTransClient::init()
{
    m_pClient = new QTcpSocket(this);
}
