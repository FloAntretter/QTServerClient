#include "client.h"
#include "ui_client.h"
#include <QtNetwork/QHostAddress>

Client::Client(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Client)
{
    ui->setupUi(this);
    ui->ipLineEdit->setInputMask("000.000.000.000");
    connect(&client, SIGNAL(readyRead()), this, SLOT(startRead()));
}

Client::~Client()
{
    delete ui;
    client.close();
}

void Client::startWrite()
{
    QString factor1 = ui->factor1LineEdit->text();
    QString factor2 = ui->factor2LineEdit->text();
    QString messageString = factor1 + "MUL" + factor2;
    char * message = {};
    QByteArray messageByteArray = messageString.toLatin1();
    message = messageByteArray.data();
    if(factor1 != "" && factor2 != "")
    {
        qDebug() << message;
        client.write(message);
    }
    else if(factor1 == "")
    {
        QMessageBox noFactor1;
        noFactor1.setWindowTitle("Kein Faktor1");
        noFactor1.setText("Bitte geben Sie eine Zahl für Faktor1 ein.");
        noFactor1.exec();
    }
    else if(factor2 == "")
    {
        QMessageBox noFactor2;
        noFactor2.setWindowTitle("Kein Faktor2");
        noFactor2.setText("Bitte geben Sie eine Zahl für Faktor2 ein.");
        noFactor2.exec();
    }
}

void Client::startRead()
{
    qDebug() << "sdfasdfwew dadesffaggzt";
    QByteArray result = client.readAll();
    ui->productLineEdit->setText(QString::fromLocal8Bit(result));
}

void Client::on_quitButton_clicked()
{
    close();
}

void Client::on_connectButton_clicked()
{
    if(connected == false)
    {
        connect(&client, SIGNAL(connected()), this, SLOT(startWrite()));
        connected = true;
    }
    if(ui->connectButton->text() == "Verbinden")
    {
        client.close();
        connectToServer();
        ui->connectButton->setText("Update");
    }
    else
    {
        startWrite();
    }
}

void Client::on_ipLineEdit_textChanged()
{
    connected = false;
    ui->connectButton->setText("Verbinden");
}

void Client::on_portLineEdit_textChanged()
{
    ui->connectButton->setText("Verbinden");
}

void Client::connectToServer()
{
    QString address = ui->ipLineEdit->text();
    QHostAddress addr(address);
    quint16 port = ui->portLineEdit->text().toUInt();

    if(!addr.setAddress(ui->ipLineEdit->text()))
    {
        QMessageBox invalidIP;
        invalidIP.setWindowTitle("Ungültige IP-Adresse");
        invalidIP.setText("Bitte geben Sie eine gültige Adresse ein.");
        invalidIP.exec();
    }

    if(ui->portLineEdit->text() != "" &&
            ui->portLineEdit->text().toInt() > 1023)
    {
        port = ui->portLineEdit->text().toUInt();
    }
    else
    {
        QMessageBox invalidPort;
        invalidPort.setWindowTitle("Ungueltiger Port");
        invalidPort.setText("Bitte geben Sie einen Port von 1024 bis 62000 ein.");
        invalidPort.exec();
    }

    client.connectToHost(addr, port);
}
