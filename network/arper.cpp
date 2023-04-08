#include "arper.h"

Arper::Arper(int arpingPort):
    arpingPort(arpingPort)
{

}

int Arper::parseArpMsg()
{
    arpMessage = "AMUR:";
    arpMessage += System::Info::getMachineID();
    return 0;
}

int Arper::broadcastMsg(int broadcast_port, std::string &broadcastMsg)
{
    // Creating socket
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (sockfd == -1) {
        std::cerr << "Failed to create socket." << std::endl;
        return -1;
    }

    // Allow sending broadcast messages
    int optval = 1;
    if (setsockopt(sockfd, SOL_SOCKET, SO_BROADCAST, &optval, sizeof optval) == -1) {
        std::cerr << "Failed to set socket options." << std::endl;
        return -2;
    }

    // Setting the address and port
    struct sockaddr_in addr;
    std::memset(&addr, 0, sizeof addr);
    addr.sin_family = AF_INET;
    addr.sin_port = htons(broadcast_port);
    addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

    // Send message
    if (sendto(sockfd, broadcastMsg.c_str(), broadcastMsg.length(), 0, (struct sockaddr *)&addr, sizeof addr) == -1) {
        std::cerr << "Failed to send ARP broadcast message." << std::endl;
        return -3;
    }

    close(sockfd);
    return 0;
}

int Arper::startArpingService(bool &connected)
{
    int res = 0;
    res = parseArpMsg();

    // Send arm msg loop thread
    std::thread sender([&]()
    {
        // Send arp message every second if not connected
        while(!connected){
            broadcastMsg(arpingPort, arpMessage);
            std::this_thread::sleep_for(1000ms);
        }
    });
    sender.detach();

    return res;
}

