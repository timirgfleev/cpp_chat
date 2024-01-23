#ifndef CONNECTION_H
#define CONNECTION_H

#include <QTcpSocket>

class Connection : public QObject
{
    Q_OBJECT

public:
    Connection(QObject *parent = nullptr);
    ~Connection();

    void connectToHost(const QString &hostName, quint16 port);

signals:
    void messageReceived(const QString &message);
public slots:
    void getMessages();
    void sendMessage(const QString &message);
private slots:
    void onReadyRead();
protected:
    void sendJson(QJsonObject& to_send);
private:
    QTcpSocket *socket;
};

#endif // CONNECTION_H
