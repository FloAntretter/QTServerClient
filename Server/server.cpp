#include "server.h"
#include "ui_server.h"

using namespace std;

Server::Server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);
    ui->portLineEdit->setText("12345");
    ui->zahl1Label->hide();
    ui->zahl2Label->hide();
    ui->calculationLabel->hide();

    connect(&server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));

    server.listen(QHostAddress::Any, 12345);
}

Server::~Server()
{
    delete ui;
    server.close();
}

void Server::acceptConnection()
{
    client = server.nextPendingConnection();

    connect(client, SIGNAL(readyRead()), this, SLOT(startRead()));

    QHostAddress clientIPAddress = client->localAddress();
    QString clientIPString = clientIPAddress.toString();
    ui->connectionLabel->setText("Verbindung mit " + clientIPString + " wurde hergestellt.");
}

void Server::startRead()
{
    char buffer[1024];

    client->read(buffer, client->bytesAvailable());
    client->close();

    QString bufferString(buffer);

    int slicePos = bufferString.indexOf("\b");
    bufferString = bufferString.left(slicePos);

    qDebug() << "Buffer: " << bufferString;

    slicePos = bufferString.indexOf(".,");
    QString factor2String = bufferString.right(slicePos-1);
    QString factor1String = bufferString.left(slicePos);

    int factor1 = factor1String.toInt();
    int factor2 = factor2String.toInt();
    int product = factor1 * factor2;

    QString productString = QString::number(product);

    QString calculation = factor1String + " * " + factor2String + " = " + productString;
    qDebug() << calculation;
}

