#include "scadadevice.h"

ScadaDevice::ScadaDevice()
{
    name = "noname";
    factoryData = "nodata";
    deviceState = STATE_ON;
}

ScadaDevice::~ScadaDevice()
{

}



int ScadaDevice::getUUID(){
    return uuid;
}

Packet ScadaDevice::getSettingsPacket()
{
    Packet packet;
    packet.setPacketID(Packet::SETTINGS);
    packet.setDeviceID(this->uuid);
    packet.addNumericData(this->deviceState);
    return packet;
}

bool ScadaDevice::settingsReceived(Packet *settings)
{
    if(settings->getNumericData()->size()==1)
    {
        this->deviceState = (deviceState_enum)settings->getNumericData()->at(0);
        return true;
    }
    return false;
}
