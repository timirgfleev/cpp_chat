#include "connection.h"

#include <QJsonDocument>
#include <QJsonObject>

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
    // Create a QJsonObject
    QJsonObject json;
    json["action"] = "message";
    json["message"] = message;

    // Convert the QJsonObject to a QJsonDocument
    QJsonDocument jsonDoc(json);

    // Convert the QJsonDocument to a QByteArray
    QByteArray jsonData = jsonDoc.toJson();

    // Send the JSON data
    socket->write(jsonData);
}


void Connection::onReadyRead()
{
    QTextStream stream(socket);
    emit messageReceived(stream.readAll());
}
