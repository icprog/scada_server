#include "sensorconnection.h"

SensorConnection::SensorConnection(QTcpSocket *socket) : DeviceConnection(socket)
{

}

SensorConnection::~SensorConnection()
{

}

bool SensorConnection::dataReceived(Packet *data)
{
    bool retval = Sensor::dataReceived(data);
    if(retval) enqueueData(currentValue);
    return retval;
}

//double SensorConnection::getData()
