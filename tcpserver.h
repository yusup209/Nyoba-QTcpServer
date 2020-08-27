#ifndef TCPSERVER_H
#define TCPSERVER_H

#include <QObject>
#include <QDebug>
#include <QTcpServer>
#include <QTcpSocket>

class TcpServer : public QObject
{
    Q_OBJECT
public:
    TcpServer(QObject *parent = nullptr);

public slots:
    void newConnection();

private:
    QTcpServer *server;
    QTcpSocket *socket;
    bool stopServer = false;

private slots:
    void readyToRead();
signals:

};

#endif // TCPSERVER_H
