#include "connection.h"

Connection::Connection(QObject *parent)
    : QObject(parent)
    , socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::readyRead, this, &Connection::onReadyRead);
}

Connection::~Connection(){
    delete socket;
}

void Connection::connectToHost(const QString &hostName, quint16 port)
{
    socket->connectToHost(hostName, port);
}

void Connection::sendMessage(const QString &message)
{
    socket->write(message.toUtf8());
}


void Connection::onReadyRead()
{
    QTextStream stream(socket);
    emit messageReceived(stream.readAll());
}
