#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTcpServer>
#include "llstcpdef.h"

class LLSTcpTransServer;
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
    void mouseReleaseEvent(QMouseEvent *event);

private:
    void init();
    bool isSocketReadyRead(QTcpSocket* client);

private:
    LLSTcpTransServer*      m_tcpServer = nullptr;

};

#endif // MAINWINDOW_H
