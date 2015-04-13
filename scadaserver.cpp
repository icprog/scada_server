#include "scadaserver.h"

ScadaServer::ScadaServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    deviceList = new QList<DeviceConnection>;
    devicesConnected = new QList<QTcpSocket*>;
//    signalMapper = new QSignalMapper(this);
    connect(this->server, SIGNAL(newConnection()), this, SLOT(onNewDeviceConnected()));
}

ScadaServer::~ScadaServer()
{
    delete deviceList;
//    qDeleteAll(devicesConnected);
    delete devicesConnected;
}

bool ScadaServer::startServer(int portNumber)
{
    return server->listen(QHostAddress::Any, portNumber);
}



void ScadaServer::onNewDeviceConnected()
{

    QTcpSocket* newDevice = server->nextPendingConnection();
    devicesConnected->append(newDevice);
    connect(newDevice, SIGNAL(readyRead()), this, SLOT(onDeviceDataRx()));
}


void ScadaServer::onDeviceDataRx()
{
    QTcpSocket *socket = dynamic_cast<QTcpSocket*>(sender());
    QByteArray rxData = socket->readAll();
   Packet packet;
    QList<Packet> packetList;
    while(packet.decode(&rxData)) //there can be more packets which came together
    {
        packetList.append(packet); //we will separate them and put into list
    }
    foreach(Packet element, packetList) //There may be many packets in one stream readout
    {
        if(element.getPacketType()==Packet::SENSOR_INIT) //we've got new sensor
        {
            ScadaDevice* dev = new Sensor();
            dev->initReceived(element);
            deviceList->append(DeviceConnection(dev,socket)); //append new device to connection list
        }
//        if(element.getPacketType()==Packet::REGULATOR_INIT)
//        {
//            ScadaDevice* device = new Requlator();
//            deviceList->append(device);
//        }
        if(element.getPacketType()==Packet::SENSOR_DATA)
        {
            ScadaDevice* dev = findDevice(element.getDeviceID());
            if(dev!=NULL)
            {
                dev->dataReceived(element);
            }
        }
//        if(element.getPacketType()==Packet::REGULATOR_DATA)
//        {

//        }
    }

}


ScadaDevice* ScadaServer::findDevice(int uuid)
{
    for(int i = 0; i<deviceList->size(); i++)
    {
        DeviceConnection device = deviceList->at(i);
        if(device.getDevice()->getUUID()==uuid)
        {
            return device.getDevice();
        }
    }
    return NULL;
}
