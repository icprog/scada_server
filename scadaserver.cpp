#include "scadaserver.h"

ScadaServer::ScadaServer(QObject *parent) : QObject(parent)
{
//    timer = new QTimer(this);
//    connect(this->timer, SIGNAL(timeout()), this, SLOT(onServerInterval()));
    server = new QTcpServer(this);
    deviceList = new QList<ScadaDevice*>;
    hmiList = new QList<HMI_Connection*>;
    devicesConnected = new QList<QTcpSocket*>;
//    signalMapper = new QSignalMapper(this);
    connect(this->server, SIGNAL(newConnection()), this, SLOT(onNewDeviceConnected()));
    connect(this->server, SIGNAL(acceptError(QAbstractSocket::SocketError)), this, SLOT(onServerError(QAbstractSocket::SocketError)));
}

ScadaServer::~ScadaServer()
{
    delete deviceList;
//    qDeleteAll(devicesConnected);
    delete hmiList;
    delete devicesConnected;
}

bool ScadaServer::startServer(int portNumber)
{
    qDebug() << "Server started.";
    return server->listen(QHostAddress::Any, portNumber);
}



void ScadaServer::onNewDeviceConnected()
{

    qDebug() << "New device connected";
    QTcpSocket* newDevice = server->nextPendingConnection();
    devicesConnected->append(newDevice);
    connect(newDevice, SIGNAL(readyRead()), this, SLOT(onDeviceDataRx()));
    connect(newDevice, SIGNAL(disconnected()), this, SLOT(onDeviceDisconnected()));
    connect(newDevice, SIGNAL(error(QAbstractSocket::SocketError)),this,SLOT(onSocketError(QAbstractSocket::SocketError)));


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
            qDebug() << "Sensor INIT packet received.";
            SensorConnection* sensor = new SensorConnection(socket); //create new SensorConnection, assign him socket
            if(sensor->initReceived(&packet))  //call method to process received data,
            {       //if init data correct
                ScadaDevice* device = sensor;
                deviceList->append(device); //append new device to connection list
                foreach(HMI_Connection* hmi, *hmiList)
                {
                    hmi->sendDeviceList(deviceList);  //tell all the HMIs that there's a new buddy
                }
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
        if(packet.getPacketType()==Packet::HMI_INIT)
        {
            qDebug() << "HMI INIT packet received.";
            HMI_Connection* device = new HMI_Connection(socket);
            if(device->initReceived(&packet))
            {
                hmiList->append(device);    //append new HMI to list of HMIs, to easy broadcast them new devices
                device->sendDeviceList(deviceList);
                ScadaDevice* hmi = device;
                deviceList->append(hmi);  //append new HMI to list of all devices (as ScadaDevice)
            }
            else
            {
                socket->disconnectFromHost();
                delete device;
            }
        }
//        if(packet.getPacketType()==Packet::HMI_WISHLIST)
//        {
//            ScadaDevice* dev = findDevice(packet.getDeviceID());
//            HMI_Connection* hmi = dynamic_cast<HMI_Connection*>(dev);
//            hmi->settingsReceived(packet);
//        }
        if(packet.getPacketType()==Packet::DATA)
        {
              ScadaDevice* dev = findDevice(packet.getDeviceID());

            if(dev!=NULL)
            {
                dev->dataReceived(&packet);
                for(size_t i =0; i<hmiList->size(); i++) //for each HMI...
                {
                    HMI_Connection* hmi = hmiList->at(i);
                    if(hmi->isOnWishlist(dev->getUUID())) //Check if data sender is on wishlist...
                    {
                        hmi->getSocket()->write(dev->getDataPacket().encode()); //If so, forward its data to HMI
                    }
                }
            }
        }
        if(packet.getPacketType()==Packet::SETTINGS)
        {
            qDebug() << "SETTINGS packet received.";
            ScadaDevice *dev = findDevice(packet.getDeviceID());
            if(dev)
            {
                HMI_Connection* hmi = dynamic_cast<HMI_Connection*>(dev); //additionally, check if dev is a HMI
                if(hmi)  //if so, settings packet contains wishlist
                {
                   hmi->settingsReceived(&packet);
                }
                else
                {
                    dev->settingsReceived(&packet);
                    DeviceConnection* connection = dynamic_cast<DeviceConnection*>(dev);
                    if(connection)
                    {
                        connection->getSocket()->write(dev->getSettingsPacket().encode());
                    }
                }
            }
        }
//        if(element.getPacketType()==Packet::REGULATOR_DATA)
//        {

//        }
    }

}

void ScadaServer::onDeviceDisconnected()
{
    qDebug() << "Device disconnected.";
    QTcpSocket *socket = dynamic_cast<QTcpSocket*>(sender());
    for(int i = 0; i<deviceList->size(); i++)
    {
        DeviceConnection *device = dynamic_cast<DeviceConnection*>(deviceList->at(i));
        if(device->getSocket() == socket)
        {
            for(int j=0; j<hmiList->size(); j++)
            {
                HMI_Connection* hmi = static_cast<HMI_Connection*>(device);
                if(hmi->getSocket()==socket)
                {
//                    delete hmiList->at(i);
                    hmiList->removeAt(j);
                    break;
                }
            }
            delete deviceList->at(i);
            deviceList->removeAt(i);
            return;
        }
    }
    for(size_t i =0; i<hmiList->size(); i++) //for each HMI...
    {
        HMI_Connection* hmi = hmiList->at(i);
        hmi->sendDeviceList(deviceList);
    }
}


void ScadaServer::onServerError(QAbstractSocket::SocketError error)
{
    qDebug() << "An error occured: " + QString::number(error)<<endl;
    qDebug() << server->errorString();
}

void ScadaServer::onSocketError(QAbstractSocket::SocketError error)
{
    QTcpSocket *socket = dynamic_cast<QTcpSocket*>(sender());
    qDebug() << socket->errorString();
}

ScadaDevice* ScadaServer::findDevice(int uuid)
{
    for(int i = 0; i<deviceList->size(); i++)
    {
        ScadaDevice *device = deviceList->at(i);
        if(device->getUUID()==uuid)
        {
            return device;
        }
    }
    return NULL;
}


