#include "page0_talk.h"
#include "ui_page0_talk.h"

Page0_talk::Page0_talk(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Page0_talk)
{
    ui->setupUi(this);
}

Page0_talk::~Page0_talk()
{
    delete ui;
}

void Page0_talk::on_sendButton_clicked()
{

    emit sendButtonClicked(ui->textSend->toPlainText());
    ui->textSend->clear();

}

void Page0_talk::receive_chat(const QString &text)
{
    ui->textChat->setText(text);
}


void Page0_talk::on_updateButton_clicked()
{
    emit updateButton_clicked();
}

