#ifndef LLSTCPTRANSSERVER_H
#define LLSTCPTRANSSERVER_H

#include "llstcptransbase.h"
class QTcpServer;
class QTcpSocket;
class QTimer;
using namespace  TcpMeaasge;

class LLSTcpTransServer : public LLSTransBase{
    Q_OBJECT
public:
    explicit LLSTcpTransServer(QObject* parent = nullptr);

    void bind(QVariant ip,QVariant port);

    void write(QString& msg);
    void write(QJsonObject& msg);

private:
    void write(LocalMeaasg& message);

private slots:
    /**
    * @brief  新客户端接入
    */
    void onNewConnect();
    /**
    * @brief  检测客户端是否在线
    */
    void onCheakClient();
    /**
    * @brief  移除客户端
    */
    void removeClient(QTcpSocket* client);

private:
    QTcpServer*             m_pTcpServer = nullptr;
    QList<QTcpSocket*>      m_socketList;
    QTimer*                 m_pTimer = nullptr;

};

#endif // LLSTCPTRANSSERVER_H
