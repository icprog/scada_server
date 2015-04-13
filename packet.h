#ifndef PACKET_H
#define PACKET_H
#include <QList>
#include <QString>
#include <QStringList>


class Packet
{
public:
    enum PacketID_enum{
        SENSOR_INIT,
        SENSOR_DATA,
        REGULATOR_INIT,
        REGULATOR_DATA,
        HMI_INIT
    };

    Packet();
    ~Packet();

    QByteArray encode();
    bool decode(QByteArray *data);

    int getPacketType();
    int getDeviceID();
    QList<QString>* getBriefData();
    QList<double>* getNumericData();

    void setPacketID(int id);
    void setDeviceID(int id);
    void addBriefData(QString data);
    void addNumericData(double data);

private:

    PacketID_enum packetID;
    int deviceID;
    QList<QString>* briefData;
    QList<double>* numericData;

    static const char START_CHAR = '!';
    static const char SEPARATOR = '|';
    static const char END_CHAR = '\n';

};

#endif // PACKET_H
