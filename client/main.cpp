#include <QApplication>
#include <QVBoxLayout>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>
#include <QTcpSocket>

int main(int argc, char **argv)
{
    QApplication app(argc, argv);

    QWidget window;
    QVBoxLayout layout(&window);

    QTextEdit chatHistory;
    chatHistory.setReadOnly(true);
    layout.addWidget(&chatHistory);

    QTextEdit messageInput;
    layout.addWidget(&messageInput);

    QPushButton sendButton("Send");
    layout.addWidget(&sendButton);

    QTcpSocket socket;
    socket.connectToHost("localhost", 1234);

    QObject::connect(&socket, &QTcpSocket::readyRead, [&](){
        chatHistory.append(socket.readAll());
    });

    QObject::connect(&sendButton, &QPushButton::clicked, [&](){
        socket.write(messageInput.toPlainText().toUtf8());
        messageInput.clear();
    });

    window.show();

    return app.exec();
}