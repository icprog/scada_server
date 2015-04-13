#include "deviceinterface.h"

DeviceConnection::DeviceConnection(ScadaDevice *device, QTcpSocket* socket)
{
    this->device =device;
    this->socket =socket;
}

DeviceConnection::~DeviceConnection()
{
    delete device;
    delete socket;
}

QTcpSocket* DeviceConnection::getSocket()
{
    return socket;
}

ScadaDevice* DeviceConnection::getDevice()
{
    return device;
}
