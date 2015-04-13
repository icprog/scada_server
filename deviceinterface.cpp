#include "deviceinterface.h"

DeviceConnection::DeviceConnection(ScadaDevice *device,QTcpSocket* socket)
{
    this->dev =device;
    this->soc =socket;
}

DeviceConnection::~DeviceConnection()
{
    delete dev;
//    delete socket;
}

QTcpSocket* DeviceConnection::getSocket()
{
    return soc;
}

ScadaDevice* DeviceConnection::getDevice()
{
    return dev;
}
