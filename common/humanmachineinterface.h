#ifndef HUMANMACHINEINTERFACE_H
#define HUMANMACHINEINTERFACE_H

#include "scadadevice.h"

class HumanMachineInterface : public ScadaDevice
{
public:
    HumanMachineInterface();
    ~HumanMachineInterface();
    Packet getDataPacket();
    Packet getInitPacket();
    Packet getSettingsPacket();
    bool initReceived(Packet *init);
    bool dataReceived(Packet *data);
    bool settingsReceived(Packet *settings);

    bool appendToWishlist(ScadaDevice* device);

private:
    QString hmiBrief;

protected:
    QList<int> wishList;


};

#endif // HUMANMACHINEINTERFACE_H
