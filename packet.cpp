#include "packet.h"

Packet::Packet()
{
    briefData = new QList<QString>;
    numericData = new QList<double>;
}

Packet::Packet(const Packet &packet)
{
    briefData = new QList<QString>(*packet.getBriefData());
    numericData = new QList<double>(*packet.getNumericData());
    packetID = (PacketID_enum)packet.getPacketType();
    deviceID = packet.getDeviceID();

}

Packet::~Packet()
{
    if(briefData!=NULL && numericData != NULL)
    {
        delete briefData;
        delete numericData;
        briefData = NULL;
        numericData = NULL;
    }

}

Packet &Packet::operator= (const Packet &packet)
{
    if(this != &packet)
    {
        QList<QString> *briefDataN = new QList<QString>(*packet.getBriefData());
       QList<double> *numericDataN = new QList<double>(*packet.getNumericData());
        packetID = (PacketID_enum)packet.getPacketType();
        deviceID = packet.getDeviceID();

        delete briefData;
        delete numericData;
        briefData = briefDataN;
        numericData = numericDataN;
    }
    return *this;
}



//Packet format: ![PacketID]|[DeviceID]|#b|[brief1]|...|[briefN]|#n|[numeric1]|...|[numericN]\n
//example: !|#p|0|#d|1|#b|Pressure|Manufacturer unknown|#n|-100|+100|\n
QByteArray Packet::encode()
{
    QByteArray encodedData;
    encodedData.append(START_CHAR);                         //'!' is packet start character
    encodedData.append(SEPARATOR);
    encodedData.append("#p");
    encodedData.append(SEPARATOR);
    encodedData.append(QString::number((int)packetID,10));  //Append Packet ID
    encodedData.append(SEPARATOR);                          //'|' character as separator
    encodedData.append("#d");
    encodedData.append(SEPARATOR);
    encodedData.append(QString::number(deviceID,10));       //Append Device UUID
    encodedData.append(SEPARATOR);
    encodedData.append("#b");       //brief data identificator
    encodedData.append(SEPARATOR);
    foreach(QString element, *briefData)     //append brief data
    {
        encodedData.append(element);
        encodedData.append(SEPARATOR);
    }
    encodedData.append("#n");  //numeric data identificator
    encodedData.append(SEPARATOR);
    foreach(double element, *numericData)   //append numeric data
    {
        encodedData.append(QString::number(element));
        encodedData.append(SEPARATOR);
    }
    encodedData.append(END_CHAR);
    return encodedData;
}

bool Packet::decode(QByteArray *data)
{

//    QString splitSeparator;
//    splitSeparator.append(SEPARATOR);
    QStringList splitData = (QString::fromLocal8Bit(*data).split(SEPARATOR));

    size_t i = 0;
    while((splitData.at(i)).contains("!") && i<data->size()) //After this loop i points to START_CHAR
        i++;

    if(splitData.at(i).contains("#p"))
        this->packetID = (PacketID_enum)splitData.at(++i).toInt();
    else return false;
    i++;
    if(splitData.at(i).contains("#d"))
        this->deviceID = splitData.at(++i).toInt();
    else return false;
    i++;
    if(splitData.at(i++)=="#b")
        while(splitData.at(i)!="#n" && i<data->size())
        {
            this->briefData->append(splitData.at(i));
            i++;
        }
    else return false;
    if(splitData.at(i++)=="#n")
        while(!splitData.at(i).contains("\n") && i<data->size())
        {
            this->numericData->append(splitData.at(i).toDouble());
            i++;
        }
    else return false;
    data->remove(0,i);
    return true;
}

int Packet::getPacketType() const
{
    return packetID;
}
int Packet::getDeviceID() const
{
    return deviceID;
}

QList<QString> *Packet::getBriefData() const
{
    return briefData;
}

QList<double>* Packet::getNumericData() const
{
    return numericData;
}

void Packet::setPacketID(int id)
{
    this->packetID = (PacketID_enum) id;
}
void Packet::setDeviceID(int id)
{
    this->deviceID = id;
}
void Packet::addBriefData(QString data)
{
    this->briefData->append(data);
}
void Packet::addNumericData(double data)
{
    this->numericData->append(data);
}
