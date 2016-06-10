#include "server.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication application(argc, argv);
    Server server;
    server.show();

    return application.exec();
}
