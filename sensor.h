#ifndef SENSOR_H
#define SENSOR_H
#include <QObject>
#include <QString>

#include "scadadevice.h"
#include "packet.h"

class Sensor : public ScadaDevice
{

public:
    Sensor();
    ~Sensor();
    Packet getDataPacket();
    Packet getInitPacket();
    bool dataReceived(Packet *data);
    bool initReceived(Packet *init);
    bool settingsReceived(Packet *settings);

private:
//    int deviceID;
    QString measurandName;
    QString measurandUnit;
    double rangeMin;
    double rangeMax;
    double samplingPeriod;

protected:
    double currentValue;

};

#endif // SENSOR_H
