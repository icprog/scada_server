#include <QCoreApplication>
#include "scadaserver.h"

int main(int argc, char *argv[])
{
    if(argc != 2)
    {
        qDebug() << "Usage: scada_server [port number]" <<endl;
        return -1;
    }

    QCoreApplication a(argc, argv);
    ScadaServer server;
    server.startServer(QString(argv[1]).toInt());
    return a.exec();
}
