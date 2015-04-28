#ifndef HMI_CONNECTION_H
#define HMI_CONNECTION_H
#include <QTcpSocket>
#include <QList>
#include "common/scadadevice.h"
#include "common/humanmachineinterface.h"
#include "deviceinterface.h"


class HMI_Connection : public HumanMachineInterface, public DeviceConnection
{
public:
    HMI_Connection(QTcpSocket* socket);
    ~HMI_Connection();

    QList<int>* getWishlist();
    bool isOnWishlist(int uuid);
    void sendDeviceList(QList<ScadaDevice*>* deviceList);
};

#endif // HMI_CONNECTION_H
