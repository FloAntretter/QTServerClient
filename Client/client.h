#ifndef CLIENT_H
#define CLIENT_H

#include <QMainWindow>
#include <QString>
#include <QtNetwork/QTcpSocket>
#include <QMessageBox>

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
    void startWrite();
    void startRead();

private slots:
    void on_quitButton_clicked();

    void on_connectButton_clicked();

    void on_ipLineEdit_textChanged();

    void on_portLineEdit_textChanged();

private:
    Ui::Client *ui;
    QTcpSocket client;
    void connectToServer();
    bool connected = false;
};

#endif // CLIENT_H
