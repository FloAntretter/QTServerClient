#include "server.h"
#include "ui_server.h"

using namespace std;

Server::Server(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::Server)
{
    ui->setupUi(this);

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
    char buffer[1024];

    client->read(buffer, client->bytesAvailable());

    QString bufferString(buffer);

    int slicePos = bufferString.indexOf("END");
    bufferString = bufferString.left(slicePos);

    slicePos = bufferString.indexOf("MUL");
    QString factor1String = bufferString.left(slicePos);
    slicePos = bufferString.size() - (slicePos + 3);
    QString factor2String = bufferString.right(slicePos);

    int factor1 = factor1String.toInt();
    int factor2 = factor2String.toInt();
    int product = factor1 * factor2;

    QString productString = QString::number(product);

    ui->factor1LineEdit->setText(factor1String);
    ui->factor2LineEdit->setText(factor2String);
    ui->productLineEdit->setText(productString);

    QByteArray resultBytes = productString.toLatin1();
    char * result = resultBytes.data();

    client->write(result);
    client->close();

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
