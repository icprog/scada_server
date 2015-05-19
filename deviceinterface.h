/**
 * \class DeviceConnection
 *
 * \brief A class to handle device connections to server
 *
 *
 *
 * \author Jakub Szlendak $Author: js $
 *
 * \version $Revision: 0.9 $
 *
 * \date $Date: 2015/05/05 14:16:20 $
 *
 * Contact: szlendak.jakub@gmail.com
 *
 * Created on: Wed Apr 13 18:39:37 2005
 *
 * $Id: doxygen-howto.html,v 1.5 2005/04/14 14:16:20 bv Exp $
 *
 */
#ifndef DEVICEINTERFACE_H
#define DEVICEINTERFACE_H
#include <QTcpSocket>
#include "common/scadadevice.h"
class DeviceConnection
{
public:
    /**
      \brief Creates an instance of DeviceConnetion.
      \param A pointer to device socket.
      */
    DeviceConnection(QTcpSocket *socket);

    ~DeviceConnection();

    /**
      \brief Gets a pointer to device associated socket.
      \retval A pointer to device socket.
      */
    QTcpSocket* getSocket();

    /**
      \brief Assignes socket to device.
      \param Pointer to device socket.
      */
    void setSocket(QTcpSocket* socket);
protected:
    void enqueueData(double data);
    double dequeueData();

private:
    QTcpSocket* soc;   //< pointer to socket
    QList<double>* buffer; //< pointer to circular buffer

};

#endif // DEVICEINTERFACE_H
