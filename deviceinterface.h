#ifndef DEVICEINTERFACE_H
#define DEVICEINTERFACE_H
#include <QTcpSocket>
#include "scadadevice.h"
class DeviceConnection
{
public:
    DeviceConnection(QTcpSocket *socket);
    ~DeviceConnection();
    QTcpSocket* getSocket();
//    ScadaDevice* getDevice();
    void setSocket(QTcpSocket* socket);
protected:
    void enqueueData(double data);
    double dequeueData();

private:
//    ScadaDevice* dev;
    QTcpSocket* soc;
    QList<double>* buffer;

};

#endif // DEVICEINTERFACE_H
