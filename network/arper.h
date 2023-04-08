#ifndef ARPER_H
#define ARPER_H

#include <thread>
#include <chrono>

#include <cstring>
#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>

#include "../system/systeminfo.h"

using namespace std::chrono_literals;

class Arper
{
    int arpingPort;
    std::string arpMessage;

    int broadcastMsg(int broadcast_port, std::string &broadcastMsg);
    int parseArpMsg();
public:
    Arper(int arpingPort);

    int startArpingService(bool &connected); // Send initial message for informing control computer about robot
};

#endif // ARPER_H
