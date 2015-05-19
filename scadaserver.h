#ifndef SCADASERVER_H
#define SCADASERVER_H

#include <QObject>
#include <QSignalMapper>
#include <QTcpServer>
#include <QTcpSocket>
#include <QTimer>

#include "deviceinterface.h"
#include "sensorconnection.h"
#include "hmi_connection.h"
#include "common/packet.h"
#include <QDebug>
//#include "sensor.h"
//#include "regulator.h"


class ScadaServer : public QObject
{
    Q_OBJECT
public:
    explicit ScadaServer(QObject *parent = 0);
    ~ScadaServer();

    bool startServer(int portNumber);

signals:

private slots:
    void onNewDeviceConnected();
    void onDeviceDataRx();
    void onDeviceDisconnected();

private:
    QList<ScadaDevice*>* deviceList;
    QList<HMI_Connection*>* hmiList;
    QTcpServer *server;
    QList<QTcpSocket*> *devicesConnected;

    QTimer* timer;


    ScadaDevice* findDevice(int uuid);

};

#endif // SCADASERVER_H
