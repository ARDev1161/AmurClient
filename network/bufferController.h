#ifndef BUFFERCONTROLLER_H
#define BUFFERCONTROLLER_H

#include "stdlib.h"

#include "control/control.h"
#include "network/protobuf/control.pb.h" 

class BufferController
{
    Control *zanyaControl;

    AmurControl *pControl;

    std::string *serializedControl;

    QString *hostName;

    QTcpServer *tcpServer = nullptr;
    QNetworkSession *networkSession = nullptr;

public:
    BufferController(Control *control, QString *hostname);

private slots:
    void sessionOpened();
    void sendControl();

private:
    void initNetwork();
    void protoByControl();
    void protoInit();
    void protoSerialize();
};

#endif // BUFFERCONTROLLER_H
