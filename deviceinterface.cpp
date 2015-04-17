#include "deviceinterface.h"

DeviceConnection::DeviceConnection(QTcpSocket* socket)
{
//    this->dev =device;
    this->soc =socket;
    buffer = new QList<double>;
}

DeviceConnection::~DeviceConnection()
{
//    delete dev;
    delete buffer;
//    delete socket;
}

QTcpSocket* DeviceConnection::getSocket()
{
    return soc;
}

//ScadaDevice* DeviceConnection::getDevice()
//{
//    return dev;
//}


void DeviceConnection::setSocket(QTcpSocket* socket)
{
    this->soc = socket;
}

void DeviceConnection::enqueueData(double data)
{
    buffer->append(data);
}

double DeviceConnection::dequeueData()
{
    return buffer->takeFirst();
}
