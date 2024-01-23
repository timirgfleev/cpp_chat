#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "connection.h"


#include <QTimer>

int main(int argc, char *argv[])
{

    QApplication a(argc, argv);

    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "qt6_client_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    MainWindow w;

    Connection c;
    c.connectToHost("localhost", 1234);

    QObject::connect(&w, &MainWindow::send_message, &c, &Connection::sendMessage);
    QObject::connect(&w, &MainWindow::request_chat_history, &c, &Connection::getMessages);
    QObject::connect(&c, &Connection::messageReceived, &w, &MainWindow::receive_chat);

    QTimer *timer = new QTimer(nullptr);
    QObject::connect(timer, &QTimer::timeout, &c, &Connection::getMessages);
    timer->start(1000);

    w.show();
    return a.exec();
}
