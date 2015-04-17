#ifndef SCADADEVICE_H
#define SCADADEVICE_H
#include "packet.h"
#include <QTcpSocket>

enum deviceState_enum
{
    STATE_ON,
    STATE_OFF,
    STATE_ERROR
};

class ScadaDevice
{
public:
    explicit ScadaDevice();
    ~ScadaDevice();

    virtual Packet getInitPacket();
    virtual Packet getDataPacket();
    virtual bool initReceived(Packet* init);
    virtual bool dataReceived(Packet* data);
    int getUUID();
protected:
    QString name;
    QString factoryData;
    deviceState_enum deviceState;
    int uuid;


};

#endif // SCADADEVICE_H
