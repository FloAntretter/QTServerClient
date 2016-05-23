#include "client.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Client w;
    w.show();
    w.start("10.0.60.41", 12345);

    return a.exec();
}
