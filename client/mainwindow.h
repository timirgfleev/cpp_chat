#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include "page0_talk.h"



QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private slots:
    void chat_send(const QString &text); //take message from child

    void on_pushButton_clicked();

    void get_chat_history();
public slots:
    void receive_chat(const QString &text);

signals:
    void request_chat_history();
    void update_chat_history(const QString &text);
    void send_message(const QString &text); //emit message from child

private:
    Ui::MainWindow *ui;
    Page0_talk * screen;
};
#endif // MAINWINDOW_H
