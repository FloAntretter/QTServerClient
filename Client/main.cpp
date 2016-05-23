#include "client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client w;
    w.show();
    w.start("127.0.0.1", 12345);

    return a.exec();
}
