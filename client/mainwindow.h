#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>


#include "page0_talk.h"

#include <QTcpSocket>

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
    void chat_send(const QString &text);

    void on_pushButton_clicked();

    void receive_chat();

private:
    Ui::MainWindow *ui;
    Page0_talk * screen;
    QTcpSocket* socket;
};
#endif // MAINWINDOW_H
