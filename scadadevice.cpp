#include "scadadevice.h"

ScadaDevice::ScadaDevice()
{

}

ScadaDevice::~ScadaDevice()
{

}

Packet ScadaDevice::getInitPacket()
{

}

Packet ScadaDevice::getDataPacket()
{

}

void ScadaDevice::initReceived(Packet init)
{

}

void ScadaDevice::dataReceived(Packet data)
{

}

int ScadaDevice::getUUID(){
    return uuid;
}

QTcpSocket* ScadaDevice::getSocket()
{
    return socket;
}

void ScadaDevice::setSocket(QTcpSocket* socket)
{
    this->socket = socket;
}