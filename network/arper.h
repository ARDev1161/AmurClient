#ifndef ARPER_H
#define ARPER_H

#include <thread>
#include <chrono>
#include <vector>
#include <cstring>

#include <unistd.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <net/if.h>
#include <sys/ioctl.h>

#include "../system/systeminfo.h"

using namespace std::chrono_literals;

class ControlMachine
{
    struct sockaddr_in m_address;
    std::chrono::system_clock::time_point last_seen;
    int m_grpcPort;

public:
    ControlMachine(const sockaddr_in &address, int grpcPort)
        : m_address(address), m_grpcPort(grpcPort)
    {}

    int grpcPort() const;
    void setGRPCPort(int newPort);

    sockaddr_in& address();
    void setAddress(const sockaddr_in &newAddress);

    std::chrono::system_clock::time_point getLastSeen() const;
    void setLastSeen(std::chrono::system_clock::time_point newLast_seen);
};

class Arper
{
    int bcast_sockfd = -1;
    int recv_sockfd = -1;
    struct sockaddr_in bcast_addr;
    struct sockaddr_in recv_addr;

    int arpingPort;
    std::string arpMessage;

    std::vector<ControlMachine*> controlMachineAddresses;

    int sendBroadcastMsg(std::string &broadcastMsg);
    int getArpMsg();

    int setSockParams(int broadcast_port);
public:
    Arper(int arpingPort);

    int startArpingService(bool &connected); // Send initial message for informing control computer about robot
};

#endif // ARPER_H
