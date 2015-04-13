#include "scadaserver.h"

ScadaServer::ScadaServer(QObject *parent) : QObject(parent)
{
    server = new QTcpServer(this);
    deviceList = new QList<ScadaDevice*>;
//    signalMapper = new QSignalMapper(this);
    connect(this->server, SIGNAL(newConnection()), this, SLOT(onNewDeviceConnected()));
}

ScadaServer::~ScadaServer()
{
    delete deviceList;
}

bool ScadaServer::startServer(int portNumber)
{
    return server->listen(portNumber);
}



void ScadaServer::onNewDeviceConnected()
{
    QTcpSocket* newDevice = server->nextPendingConnection();
    devicesConnected.append(newDevice);
    connect(newDevice, SIGNAL(readyRead()), this, SLOT(onDeviceDataRx()));
}

void ScadaServer::onDeviceDataRx()
{
    QTcpSocket *device = dynamic_cast<QTcpSocket*>(sender());
    QByteArray rxData = device->readAll();
    Packet packet;
    QList<Packet> packetList;
    while(packet.decode(rxData)) //there can be more packets which came together
    {
        packetList.append(packet); //we will separate them and put into list
    }
    foreach(Packet element, packetList)
    {
        if(element.getPacketType()==Packet::SENSOR_INIT)
        {
            ScadaDevice* device = new Sensor();
            deviceList->append(device);
        }
        if(element.getPacketType()==Packet::REGULATOR_INIT)
        {
//            ScadaDevice* device = new Requlator();
//            deviceList->append(device);
        }
        if(element.getPacketType()==Packet::SENSOR_DATA)
        {

        }
    }

}


ScadaDevice* ScadaServer::findDevice(int uuid)
{
    for(int i = 0; i<deviceList->size(); i++)
    {
        if(deviceList->at(i)->getUUID() == uuid)
        {
            return deviceList->at(i);
        }
    }
    return NULL;
}
