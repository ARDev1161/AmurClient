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
    std::string ipAddr;
    std::chrono::system_clock::time_point last_seen;
    int m_grpcPort;

public:
    ControlMachine(const sockaddr_in &address, int grpcPort)
        : m_address(address), m_grpcPort(grpcPort)
    {
        refreshIP();
    }

    int grpcPort() const;
    void setGrpcPort(int newGrpcPort);

    sockaddr_in& address();
    void setAddress(const sockaddr_in &newAddress);

    std::chrono::system_clock::time_point getLastSeen() const;
    void setLastSeen(std::chrono::system_clock::time_point newLast_seen);
    std::string getIpAddr() const;
    void refreshIP();
};


class Arper
{
    bool started = false;
    int bcast_sockfd = -1;
    int recv_sockfd = -1;
    struct sockaddr_in bcast_addr;
    struct sockaddr_in recv_addr;

    std::vector<ControlMachine*> &controlMachineAddresses;

    int bcastPort = 0;
    int arpingPort = 0;
    std::string arpMessage;

    int sendBroadcastMsg(int &sockfd, struct sockaddr_in &addr, std::string &broadcastMsg);
    int getArpMsg();

    int setSockParams(int arping_port, int bcast_port = 0);
public:
    Arper(std::vector<ControlMachine*> &controlMachineAddresses, int bcastPort, int arpingPort = 0);

    int startArpingService(bool &connected); // Send initial message for informing control computer about robot
    void stopArpingService();
};

#endif // ARPER_H
