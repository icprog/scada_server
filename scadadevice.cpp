#include "scadadevice.h"

ScadaDevice::ScadaDevice()
{
    name = "noname";
    factoryData = "nodata";
}

ScadaDevice::~ScadaDevice()
{

}



int ScadaDevice::getUUID(){
    return uuid;
}
