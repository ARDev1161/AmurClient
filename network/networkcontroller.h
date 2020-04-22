#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include "tcp/tcpclient.h"
//#include "tcp/tcpserver.h" //Not used, only client mode

class networkController
{
    std::string host;
    unsigned int port;

    TCPClient *client;
public:
    networkController();
    ~networkController();
};

#endif // NETWORKCONTROLLER_H
