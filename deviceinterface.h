#ifndef DEVICEINTERFACE_H
#define DEVICEINTERFACE_H


class DeviceConnection
{
public:
    DeviceConnection(ScadaDevice *device, QTcpSocket* socket);
    ~DeviceConnection();
private:
    ScadaDevice* device;
    QTcpSocket* socket;
    QList<double>* buffer;

};

#endif // DEVICEINTERFACE_H
