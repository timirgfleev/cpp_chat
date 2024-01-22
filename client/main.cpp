#include "mainwindow.h"

#include <QApplication>
#include <QLocale>
#include <QTranslator>

#include "connection.h"

//make layout of the window
//swithing widget through different forms



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
    QObject::connect(&c, &Connection::messageReceived, &w, &MainWindow::receive_chat);

    w.show();
    return a.exec();
}
