#ifndef SERVER_H
#define SERVER_H

#include <QMainWindow>
#include <QtNetwork/QTcpServer>
#include <QtNetwork/QTcpSocket>
#include <QMessageBox>
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

private slots:
    void on_quitButton_clicked();

    void on_confirmPortButton_clicked();

private:
    Ui::Server *ui;

    QTcpServer server;
    QTcpSocket* client;
};

#endif // SERVER_H
