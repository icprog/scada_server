#ifndef SENSORCONNECTION_H
#define SENSORCONNECTION_H

#include "sensor.h"
#include "deviceinterface.h"

class SensorConnection : public Sensor, public DeviceConnection
{
public:
    SensorConnection(QTcpSocket* socket);
    ~SensorConnection();

    bool dataReceived(Packet* data);
};

#endif // SENSORCONNECTION_H
