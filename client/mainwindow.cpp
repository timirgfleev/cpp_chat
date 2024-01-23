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




    connect(this, &MainWindow::update_chat_history, screen, &Page0_talk::receive_chat);
    connect(screen, &Page0_talk::updateButton_clicked, this, &MainWindow::get_chat_history);
    connect(screen, &Page0_talk::sendButtonClicked, this, &MainWindow::chat_send);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete screen;
}


void MainWindow::chat_send(const QString &text)
{
    //ui->pushButton->setText("send_pressed");

    emit send_message(text);
}

void MainWindow::on_pushButton_clicked()
{
    std::cout << "incremental button pushed" << std::endl;
    static int button_pushed = 0;
    ui->pushButton->setText(QString::number(button_pushed++));

    ui->statusbar->showMessage("incremental button pushed");
}

void MainWindow::receive_chat(const QString &text)
{
    std::cout << "messages received" << std::endl;
    ui->statusbar->showMessage("chat receive mainWindow call:");
    //screen->append(socket.readAll());

    emit update_chat_history(text);
}

void MainWindow::get_chat_history(){
    emit request_chat_history();
};
