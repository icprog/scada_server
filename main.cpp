#include <QCoreApplication>
#include "scadaserver.h"

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);
    ScadaServer server;
    server.startServer(8888);
    return a.exec();
}
