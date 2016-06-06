#include "server.h"
#include "ui_server.h"

using namespace std;

Server::Server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);

    foreach (const QHostAddress &address, QNetworkInterface::allAddresses()) {
        if (address.protocol() == QAbstractSocket::IPv4Protocol && address != QHostAddress(QHostAddress::LocalHost))
        {
            QString addressString = address.toString();
            QStringList addressParts = addressString.split('.');
            if(addressParts.at(0) != "169")
            {
                setWindowTitle("Server (IP: " + address.toString() + ")");
            }
        }
    }

    connect(&server, SIGNAL(newConnection()), this, SLOT(acceptConnection()));

    on_confirmPortButton_clicked();
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
    char buffer[1024] = {0};

    QString factor1String = "";
    QString factor1Decimals = "";
    QString factor2String = "";
    QString factor2Decimals = "";
    QString productString = "";

    int numberOfDecimals = 0;
    int sizeOfProduct = 0;

    double factor1 = 0;
    double factor2 = 0;
    double product = 0;

    client->read(buffer, client->bytesAvailable());

    QString bufferString(buffer);

    bufferString = bufferString.split("END").at(0);

    factor1String = bufferString.split("MUL").at(0);
    factor2String = bufferString.split("MUL").at(1);

    factor1Decimals = factor1String.split('.').at(1);
    factor2Decimals = factor2String.split('.').at(1);
    numberOfDecimals = factor1Decimals.size() + factor2Decimals.size();

    factor1 = factor1String.toDouble();
    factor2 = factor2String.toDouble();
    product = factor1 * factor2;

    productString = QString::number(product, 'g', 100);
    sizeOfProduct = numberOfDecimals + productString.split('.').at(0).size();
    if(sizeOfProduct > 37)
    {
        sizeOfProduct = 37;
    }
    productString = QString::number(product, 'g', sizeOfProduct);

    ui->factor1LineEdit->setText(factor1String);
    ui->factor2LineEdit->setText(factor2String);
    ui->productLineEdit->setText(productString);

    QByteArray resultBytes = productString.toLatin1();
    char * result = resultBytes.data();

    client->write(result);

    ui->resultSentLabel->setText("Das Ergebnis wurde zurückgesendet.");
}


void Server::on_quitButton_clicked()
{
    close();
}

void Server::on_confirmPortButton_clicked()
{
    server.close();

    int port = 12345;
    QString portString;
    if(ui->portLineEdit->text() != "" &&
            ui->portLineEdit->text().toInt() > 1023)
    {
        portString = ui->portLineEdit->text();
        port = portString.toInt();
    }
    else
    {
        QMessageBox invalidPort;
        invalidPort.setWindowTitle("Ungueltiger Port");
        invalidPort.setText("Bitte geben Sie einen Port von 1024 bis 62000 ein.");
        invalidPort.exec();
    }

    server.listen(QHostAddress::Any, port);
}
