#include "humanmachineinterface.h"

HumanMachineInterface::HumanMachineInterface()
{

}

HumanMachineInterface::~HumanMachineInterface()
{

}

bool HumanMachineInterface::initReceived(Packet *init)
{
    this->uuid = init->getDeviceID();
    QList<QString>* brief = init->getBriefData();
    QList<double>* numeric = init->getNumericData();
    if(brief->size() == 6)
    {
        name = brief->at(1);
        factoryData = brief->at(3);
        hmiBrief = brief->at(5);
        return true;
    }
    return false;

}

bool HumanMachineInterface::dataReceived(Packet *data)
{

}

bool HumanMachineInterface::settingsReceived(Packet *settings)
{
    if(settings->getNumericData()->empty())
        return false;
    foreach(double data, *(settings->getNumericData()))
    {
        wishList.append((deviceState_enum)data);
    }
    return true;

}

Packet HumanMachineInterface::getDataPacket()
{

}

Packet HumanMachineInterface::getInitPacket()
{
    Packet packet;
    packet.setPacketID(Packet::HMI_INIT);
    packet.setDeviceID(this->uuid);
    packet.addBriefData("name");
    packet.addBriefData(name);
    packet.addBriefData("factory_data");
    packet.addBriefData(factoryData);
    packet.addBriefData("hmi_brief");
    packet.addBriefData(hmiBrief);
    return packet;
}

Packet HumanMachineInterface::getSettingsPacket()
{
    Packet packet;
    packet.setPacketID(Packet::SETTINGS);
    packet.setDeviceID(this->uuid);
    foreach(int element, wishList)
    {
        packet.addNumericData(double(element));
    }
    return packet;
}


bool HumanMachineInterface::appendToWishlist(ScadaDevice* device)
{
    for(size_t i; i<wishList.size();i++)
    {
        if(wishList[i]==device->getUUID())
            return false;
    }
    wishList.append(device->getUUID());
    return true;
}
