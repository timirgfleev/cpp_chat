#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <iostream>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow),
    screen(new Page0_talk)
{
    ui->setupUi(this);

    ui->stackedWidget->addWidget(screen);
    ui->stackedWidget->setCurrentWidget(screen);
//    loginWidget = qobject_cast<LoginWidget*>(ui->stackedWidget.widget(0));





    connect(screen, &Page0_talk::sendButtonClicked, this, &MainWindow::chat_send);


    //shit code here on now!
    socket = new QTcpSocket(this);
    socket->connectToHost("localhost", 1234);

    connect(socket, &QTcpSocket::readyRead, [this]() {
        QString text = socket->readAll();
        screen->receive_chat(text);
    });
}

MainWindow::~MainWindow()
{
    delete ui;
    delete screen;
    delete socket;
}


void MainWindow::chat_send(const QString &text)
{
    //ui->pushButton->setText("send_pressed");

    socket->write(text.toUtf8());
}

void MainWindow::on_pushButton_clicked()
{
    std::cout << "incremental button pushed" << std::endl;
    static int button_pushed = 0;
    ui->pushButton->setText(QString::number(button_pushed++));

    ui->statusbar->showMessage("incremental button pushed");
}
void MainWindow::receive_chat()
{
    std::cout << "incremental button pushed" << std::endl;
    ui->statusbar->showMessage("chat receive mainWindow call:");
    //screen->append(socket.readAll());
}
