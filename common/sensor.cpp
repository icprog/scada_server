#include "sensor.h"

Sensor::Sensor() : ScadaDevice()
{
    measurandName = "nodata";
    measurandUnit = "nodata";
    deviceState = STATE_ON;
}

Sensor::~Sensor()
{

}

Packet Sensor::getDataPacket()
{
    Packet packet;
    packet.setPacketID(Packet::DATA);
    packet.setDeviceID(this->uuid);
    packet.addNumericData(deviceState);
    packet.addNumericData(currentValue);
    return packet;
}

Packet Sensor::getInitPacket()
{
    Packet packet;
    packet.setPacketID(Packet::SENSOR_INIT);
    packet.setDeviceID(this->uuid);
    packet.addBriefData(name);
    packet.addBriefData(factoryData);
    packet.addBriefData(measurandName);
    packet.addBriefData(measurandUnit);
    packet.addNumericData(rangeMax);
    packet.addNumericData(rangeMin);
    packet.addNumericData(samplingPeriod);
    return packet;
}

bool Sensor::dataReceived(Packet *data)
{
    QList<QString>* brief = data->getBriefData();
    QList<double>* numeric = data->getNumericData();
    if(numeric->size()==2)
    {
        deviceState = (deviceState_enum)numeric->at(0);
        currentValue = numeric->at(1);
        return true;
    }
    return false;

}

bool Sensor::initReceived(Packet *init)
{
    this->uuid = init->getDeviceID();
    QList<QString>* brief = init->getBriefData();
    QList<double>* numeric = init->getNumericData();
    if(brief->size() == 4 && numeric->size()==3)
    {
        name = brief->at(0);
        factoryData = brief->at(1);
        measurandName = brief->at(2);
        measurandUnit = brief->at(3);
        rangeMax = numeric->at(0);
        rangeMin = numeric->at(1);
        samplingPeriod = numeric->at(2);
        return true;
    }
    return false;

}

bool Sensor::settingsReceived(Packet *settings)
{
    if(settings->getNumericData()->size()==1)
    {
        this->deviceState = (deviceState_enum)settings->getNumericData()->at(0);
        return true;
    }
    return false;
}

