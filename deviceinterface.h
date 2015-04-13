#ifndef DEVICEINTERFACE_H
#define DEVICEINTERFACE_H
#include <QTcpSocket>
#include "scadadevice.h"
class DeviceConnection
{
public:
    DeviceConnection(ScadaDevice *device, QTcpSocket *socket);
    ~DeviceConnection();
    QTcpSocket* getSocket();
    ScadaDevice* getDevice();
private:
    ScadaDevice* dev;
    QTcpSocket* soc;
    QList<double>* buffer;

};

#endif // DEVICEINTERFACE_H
