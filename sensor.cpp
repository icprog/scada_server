#include "sensor.h"

Sensor::Sensor() : ScadaDevice()
{
    measurandName = "nodata";
    measurandUnit = "nodata";
}

Sensor::~Sensor()
{

}

Packet Sensor::getDataPacket()
{
    Packet packet;
    packet.setPacketID(Packet::SENSOR_DATA);
    packet.setDeviceID(this->deviceID);
    packet.addBriefData("meas_value");
    packet.addNumericData(currentValue);
    return packet;
}

Packet Sensor::getInitPacket()
{
    Packet packet;
    packet.setPacketID(Packet::SENSOR_INIT);
    packet.setDeviceID(this->deviceID);
    packet.addBriefData("name");
    packet.addBriefData(name);
    packet.addBriefData("factory_data");
    packet.addBriefData(factoryData);
    packet.addBriefData("measurand_name");
    packet.addBriefData(measurandName);
    packet.addBriefData("measurand_unit");
    packet.addBriefData(measurandUnit);
    packet.addBriefData("range_max");
    packet.addNumericData(rangeMax);
    packet.addBriefData("range_min");
    packet.addNumericData(rangeMin);
    packet.addBriefData("sampling_period");
    packet.addNumericData(samplingPeriod);
}

void Sensor::dataReceived(Packet *data)
{
    QList<QString>* brief = data->getBriefData();
    QList<double>* numeric = data->getNumericData();
    if(!brief->isEmpty() && !numeric->isEmpty())
    {
        if(brief->at(0)=="meas_value")
            currentValue = numeric->at(0);
    }

}

void Sensor::initReceived(Packet *init)
{
    QList<QString>* brief = init->getBriefData();
    QList<double>* numeric = init->getNumericData();
    if(brief->size() == 7 && numeric->size()==2)
    {
        name = brief->at(0);
        factoryData = brief->at(1);
        measurandName = brief->at(2);
        measurandUnit = brief->at(3);
        rangeMax = numeric->at(0);
        rangeMin = numeric->at(1);
    }

}
