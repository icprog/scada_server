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
        REGULATOR_INIT,
        HMI_INIT,
        HMI_WISHLIST,
        DATA,
        SETTINGS
    };

    Packet();
    Packet(const Packet &packet);
    ~Packet();

    Packet &operator= (const Packet &packet);

    QByteArray encode();
    bool decode(QByteArray *data);

    int getPacketType() const;
    int getDeviceID() const;
    QList<QString>* getBriefData() const;
    QList<double>* getNumericData() const;

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
