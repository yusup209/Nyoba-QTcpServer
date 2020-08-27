#include "tcpserver.h"

TcpServer::TcpServer(QObject *parent)
{
    server = new QTcpServer(this);

    connect(server, SIGNAL(newConnection()), this, SLOT(newConnection()));

    if (!server->listen(QHostAddress::Any, 1234)){
        qDebug() << "could start tcp server";
    } else {
        qDebug() << "tcp server started";
    }
}

void TcpServer::newConnection(){
    socket = server->nextPendingConnection();

    socket->write("Hello DangDut\r\n");
    socket->flush();
    socket->waitForBytesWritten(3000);

    connect(socket, SIGNAL(readyRead()), this, SLOT(readyToRead()));
}

void TcpServer::readyToRead(){
    QString hmm = socket->readAll();
    hmm = hmm.remove("\r\n", Qt::CaseSensitive);
    QString resp = "";

    if (hmm == "halo"){
        resp = "dangDut";
    } else if (hmm == "hai"){
        resp = "hello";
    } else if (hmm == "bakso"){
        resp = "abang tukang bakso, mari-mari sini, kijang satu ganti.";
    }

    if (hmm != "exit"){
        qDebug() << hmm;
        qDebug() << resp;
        resp += "\r\n";
        socket->write(resp.toLatin1());
        socket->flush();
        socket->waitForBytesWritten(3000);
    } else {
        socket->close();
        delete socket;
    }


}
