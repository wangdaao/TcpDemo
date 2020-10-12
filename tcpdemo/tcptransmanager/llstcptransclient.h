#ifndef LLSTCPTRANSCLIENT_H
#define LLSTCPTRANSCLIENT_H
#include "llstcptransbase.h"

class QTcpSocket;
class LLSTcpTransClient : public LLSTransBase{
    Q_OBJECT
public:
    explicit LLSTcpTransClient(QObject* paernt = nullptr);

    void bind(QVariant ip,QVariant port) ;
    void write(QString msg);

private:
    void init();
    void write(LocalMeaasg& message);

private:
    QTcpSocket*         m_pClient = nullptr;
};

#endif // LLSTCPTRANSCLIENT_H
