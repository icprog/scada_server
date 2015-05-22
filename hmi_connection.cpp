#include "hmi_connection.h"

HMI_Connection::HMI_Connection(QTcpSocket* socket) : DeviceConnection(socket)
{

}

HMI_Connection::~HMI_Connection()
{

}

QList<int> *HMI_Connection::getWishlist()
{
    return &wishList;
}

bool HMI_Connection::isOnWishlist(int uuid)
{

    for(size_t i=0; i<wishList.size(); i++)
    {
        if(wishList[i]==uuid)
            return true;
    }
    return false;
}

void HMI_Connection::sendDeviceList(QList<ScadaDevice *> *deviceList)
{
    foreach(ScadaDevice* device, *deviceList)
    {
        this->getSocket()->write(device->getInitPacket().encode()); //send inits of all devices to HMI
    }
}
