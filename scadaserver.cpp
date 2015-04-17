#include "scadaserver.h"

ScadaServer::ScadaServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    deviceList = new QList<ScadaDevice*>;
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
    connect(newDevice, SIGNAL(disconnected()), this, SLOT(onDeviceDisconnected()));
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

    foreach(packet, packetList) //There may be many packets in one stream readout
    {
        if(packet.getPacketType()==Packet::SENSOR_INIT) //we've got new sensor
        {
            SensorConnection* sensor = new SensorConnection(socket); //create new SensorConnection, assign him socket
            if(sensor->initReceived(&packet))  //call method to process received data,
            {       //if init data correct
                ScadaDevice* device = sensor;
                deviceList->append(device); //append new device to connection list
            }
            else
            {
                socket->disconnectFromHost();
                delete sensor;
            }
        }
//        if(element.getPacketType()==Packet::REGULATOR_INIT)   //TODO
//        {
//            ScadaDevice* device = new Requlator();
//            deviceList->append(device);
//        }
        if(packet.getPacketType()==Packet::SENSOR_DATA || packet.getPacketType()==Packet::REGULATOR_DATA) //TODO: no need of different enums
        {
              ScadaDevice* dev = findDevice(packet.getDeviceID());

            if(dev!=NULL)
            {
                dev->dataReceived(&packet);
            }
        }
//        if(element.getPacketType()==Packet::REGULATOR_DATA)
//        {

//        }
    }

}

void ScadaServer::onDeviceDisconnected()
{
    QTcpSocket *socket = dynamic_cast<QTcpSocket*>(sender());
    for(int i = 0; i<deviceList->size(); i++)
    {
        DeviceConnection *device = dynamic_cast<DeviceConnection*>(deviceList->at(i));
        if(device->getSocket() == socket)
        {
            delete deviceList->at(i);
            deviceList->removeAt(i);
            return;
        }
    }

//    ??
}

ScadaDevice* ScadaServer::findDevice(int uuid)
{
    for(int i = 0; i<deviceList->size(); i++)
    {
        ScadaDevice *device;
//        SensorConnection* connection = static_cast<SensorConnection*>(deviceList->at(i));
//        ScadaDevice* device = dynamic_cast<ScadaDevice*>(deviceList->at(i));
        if(device->getUUID()==uuid)
        {
            return device;
        }
    }
    return NULL;
}
