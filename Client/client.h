#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QString>
#include <QtNetwork/QTcpSocket>

namespace Ui {
class Client;
}

class Client : public QMainWindow
{
    Q_OBJECT

public:
    explicit Client(QWidget *parent = 0);
    ~Client();
    void start(QString address, quint16 port);

public slots:
    void startTransfer();

private:
    Ui::Client *ui;
    QTcpSocket client;
};

#endif // CLIENT_H
