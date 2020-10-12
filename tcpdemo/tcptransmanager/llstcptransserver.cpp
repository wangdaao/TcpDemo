#include "llstcptransserver.h"
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

LLSTcpTransServer::LLSTcpTransServer(QObject *parent):
    LLSTransBase(parent)
{

}

void LLSTcpTransServer::bind(QVariant ip, QVariant port)
{
    m_pTcpServer = new QTcpServer(this);
    m_pTcpServer->listen(QHostAddress(ip.toString()),port.toInt());
    connect(m_pTcpServer,&QTcpServer::newConnection,this,&LLSTcpTransServer::onNewConnect);

    m_pTimer = new QTimer(this);
    m_pTimer->setInterval(1000);
    connect(m_pTimer,&QTimer::timeout,this,&LLSTcpTransServer::onCheakClient);
}

void LLSTcpTransServer::write(QString& msg)
{
    QByteArray array = msg.toUtf8();
    TcpMessage message;
    message.head.type = type_Meaasge;
    message.head.size = MessageHeadSize + array.size();
    memcpy(message.str,array.data(),array.size());

    QByteArray sendData;
    sendData.resize(message.head.size);
    memcpy(sendData.data(),&message,message.head.size);

    for(int i = 0;i<m_socketList.count();i++){
        m_socketList.at(i)->write(sendData);
    }
}

void LLSTcpTransServer::write(QJsonObject &msg)
{
    QByteArray array = J(msg);
    TcpMessage message;
    message.head.type = type_Meaasge;
    message.head.size = MessageHeadSize + array.size();
    memcpy(message.str,array.data(),array.size());

    QByteArray sendData;
    sendData.resize(message.head.size);
    memcpy(sendData.data(),&message,message.head.size);

    for(int i = 0;i<m_socketList.count();i++){
        m_socketList.at(i)->write(sendData);
    }
}

void LLSTcpTransServer::write(LocalMeaasg &message)
{
    TcpMessage tcpMsg;
    MeaasgeFromLocalToTcp(message,tcpMsg);

    QByteArray array;
    array.resize(tcpMsg.head.size);
    memcpy(array.data(),&tcpMsg,tcpMsg.head.size);

    for(int i = 0;i<m_socketList.count();i++){
        m_socketList.at(i)->write(array);
    }
}

void LLSTcpTransServer::onNewConnect()
{
    if(m_pTcpServer->hasPendingConnections()){
        qDebug() << "===>lls<===" << __FUNCTION__ << "new client";
        QTcpSocket* socket = m_pTcpServer->nextPendingConnection();
        connect(socket,&QTcpSocket::readyRead,this,&LLSTcpTransServer::onReadData);

        m_socketList.push_back(socket);

        if(!m_pTimer->isActive()){
            m_pTimer->start();
        }
    }
}

void LLSTcpTransServer::onCheakClient()
{
    TcpMessage message;
    memset(message.str,0,sizeof(message.str));

    message.head.type = type_Heartbeat;
    message.head.size = MessageHeadSize;

    QByteArray array;
    array.resize(message.head.size);
    memcpy(array.data(),&message,message.head.size);

    for(int i = 0;i< m_socketList.count();i++){
        QTcpSocket* client = m_socketList.at(i);

        if(-1 == client->write(array)){
            removeClient(client);
        }
    }
}

void LLSTcpTransServer::removeClient(QTcpSocket *client)
{
    if(m_socketList.contains(client)){
        m_socketList.removeOne(client);
        client->deleteLater();
        client = nullptr;
    }

    if(m_socketList.count() <= 0){
        m_pTimer->stop();
    }
}
