#ifndef PAGE0_TALK_H
#define PAGE0_TALK_H

#include <QWidget>

namespace Ui {
class Page0_talk;
}

class Page0_talk : public QWidget
{
    Q_OBJECT

public:
    explicit Page0_talk(QWidget *parent = nullptr);
    ~Page0_talk();

signals:
    void sendButtonClicked(const QString &text);
    void updateButton_clicked();

private slots:
    void on_sendButton_clicked();
    void on_updateButton_clicked();

public slots:
    void receive_chat(const QString &text);

private:
    Ui::Page0_talk *ui;
};

#endif // PAGE0_TALK_H
