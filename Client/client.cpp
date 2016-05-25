#include "client.h"
#include "ui_client.h"
#include <QtNetwork/QHostAddress>

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    connect(&client, SIGNAL(connected()), this, SLOT(startWrite()));
    connect(&client, SIGNAL(readyRead()), this, SLOT(startRead()));
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

void Client::startWrite()
{
    client.write("10MUL43");
}

void Client::startRead()
{
    QByteArray result = client.readAll();
    qDebug() << QString::fromLocal8Bit(result);
}
