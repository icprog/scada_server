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

bool ScadaDevice::initReceived(Packet *init)
{

}

bool ScadaDevice::dataReceived(Packet *data)
{

}

int ScadaDevice::getUUID(){
    return uuid;
}
