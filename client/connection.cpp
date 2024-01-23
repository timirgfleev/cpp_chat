#include "connection.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>

Connection::Connection(QObject *parent)
    : QObject(parent), socket(new QTcpSocket(this))
{
    connect(socket, &QTcpSocket::readyRead, this, &Connection::onReadyRead);
}

Connection::~Connection()
{
    delete socket;
}

void Connection::connectToHost(const QString &hostName, quint16 port)
{
    socket->connectToHost(hostName, port);
}

void Connection::sendMessage(const QString &message)
{
    QJsonObject json;
    json["action"] = "message";
    json["message"] = message;
    json["chat_id"] = 0;
    sendJson(json);
}

void Connection::sendJson(QJsonObject &to_send)
{
    QJsonDocument jsonDoc(to_send);
    QByteArray jsonData = jsonDoc.toJson();
    socket->write(jsonData);
}

void Connection::getMessages()
{
    QJsonObject json;
    json["action"] = "get_messages";
    json["chat_id"] = 0;
    sendJson(json);
}

void Connection::onReadyRead()
{
    QByteArray jsonData = socket->readAll();

    QJsonParseError parseError;
    QJsonDocument jsonDoc = QJsonDocument::fromJson(jsonData, &parseError);

    // Check if the JSON was valid
    if (jsonDoc.isNull())
    {
        qWarning() << "Invalid JSON received:" << parseError.errorString();
        return;
    }

    // Convert the QJsonDocument to a QJsonObject
    QJsonObject json = jsonDoc.object();

    QStringList messageList;
    QJsonArray jsonArray = json["messages"].toArray();

    for (const auto &i : jsonArray)
    {
        messageList.append(i.toString());
    }

    QString new_chat_history = messageList.join("\n");

    emit messageReceived(new_chat_history);
}
