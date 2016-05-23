#include "client.h"
#include "ui_client.h"
#include <QtNetwork/QHostAddress>

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    connect(&client, SIGNAL(connected()), this, SLOT(startTransfer()));
}

Client::~Client()
{
    delete ui;
    client.close();
}

void Client::start(QString address, quint16 port)
{
    QHostAddress addr(address);
    client.connectToHost(addr, port);
}

void Client::startTransfer()
{
    client.write("10MUL43END");
}
