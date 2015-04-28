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
