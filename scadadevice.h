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
    virtual void initReceived(Packet init);
    virtual void dataReceived(Packet data);
    int getUUID();
    QTcpSocket* getSocket();
    void setSocket(QTcpSocket* socket);
protected:
    QString name;
    QString factoryData;
    deviceState_enum deviceState;
    QTcpSocket* socket;
private:
    int uuid;
};

#endif // SCADADEVICE_H
