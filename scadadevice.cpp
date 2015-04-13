#include "scadadevice.h"

ScadaDevice::ScadaDevice()
{
    name = "noname";
    factoryData = "nodata";
}

ScadaDevice::~ScadaDevice()
{

}

Packet ScadaDevice::getInitPacket()
{

}

Packet ScadaDevice::getDataPacket()
{

}

void ScadaDevice::initReceived(Packet *init)
{

}

void ScadaDevice::dataReceived(Packet *data)
{

}

int ScadaDevice::getUUID(){
    return uuid;
}
