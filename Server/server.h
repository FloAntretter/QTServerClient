#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QDebug>
#include <string>

namespace Ui {
class Server;
}

class Server : public QMainWindow
{
    Q_OBJECT

public:
    explicit Server(QWidget *parent = 0);
    ~Server();

public slots:
    void acceptConnection();
    void startRead();

private:
    Ui::Server *ui;

    QTcpServer server;
    QTcpSocket* client;

    int port = 12345;
};

#endif // SERVER_H
