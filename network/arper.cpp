#include "arper.h"

Arper::Arper(std::vector<ControlMachine*> &controlMachineAddresses, int bcastPort, int arpingPort):
    controlMachineAddresses(controlMachineAddresses),
    bcastPort(bcastPort),
    arpingPort(arpingPort)
{

}

int Arper::getArpMsg()
{
    arpMessage = "AMUR:";
    arpMessage += System::Info::getMachineID();
    if(arpingPort > 0)
        arpMessage += ":" + std::to_string(arpingPort);
    return 0;
}

int Arper::setSockParams(int arping_port, int bcast_port)
{
    if(bcast_port <= 0)
        bcast_port = arping_port;

    // Creating socket
    bcast_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (bcast_sockfd == -1) {
        perror("Failed to create broadcast socket");
        return -1;
    }
    // Creating socket
    recv_sockfd = socket(AF_INET, SOCK_DGRAM, 0);
    if (recv_sockfd == -1) {
        perror("Failed to create recieve socket");
        return -2;
    }

    int optval = 1;
    // Allow sending broadcast messages
    if (setsockopt(bcast_sockfd, SOL_SOCKET, SO_BROADCAST, &optval, sizeof optval) == -1) {
        perror("Failed to set broadcast socket options");
        return -3;
    }
    // Allow reusing address
    if (setsockopt(recv_sockfd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof optval) == -1) {
        perror("Failed to set recieve socket options");
        return -4;
    }

    // Setting the address and port for bcast
    std::memset(&bcast_addr, 0, sizeof bcast_addr);
    bcast_addr.sin_family = AF_INET;
    bcast_addr.sin_port = htons(bcast_port);
    bcast_addr.sin_addr.s_addr = htonl(INADDR_BROADCAST);

    // Setting the address and port for recieve
    std::memset(&recv_addr, 0, sizeof recv_addr);
    recv_addr.sin_family = AF_INET;
    recv_addr.sin_port = htons(arping_port);
    recv_addr.sin_addr.s_addr = htonl(INADDR_ANY);

    // Bind to address & port
    if (bind(recv_sockfd, (struct sockaddr *)&recv_addr, sizeof recv_addr) == -1) {
        perror("Failed to bind recieve socket");
        return -5;
    }

    return 0;
}

int Arper::sendBroadcastMsg(int &sockfd, struct sockaddr_in &addr, std::string &broadcastMsg)
{
    // Send message
    if (sendto(sockfd, broadcastMsg.c_str(), broadcastMsg.length(), 0, (struct sockaddr *)&addr, sizeof addr) == -1) {
        perror("Failed to send ARP broadcast message");
        return -1;
    }
    return 0;
}

int Arper::startArpingService(bool &connected)
{
    started = true;
    std::cout << "[INFO] Arping service started" << std::endl;

    if(getArpMsg() != 0)
        return -1;

    if(setSockParams(arpingPort, bcastPort) != 0)
        return -2;

    // Send arm msg loop thread
    std::thread BCastSender([&]()
    {
        // Send arp message every second if not connected
        while(!connected && started){
            sendBroadcastMsg(bcast_sockfd, bcast_addr, arpMessage);
            std::this_thread::sleep_for(1000ms);
        }
    });
    BCastSender.detach();


    // Wait answer msg from server
    std::thread AnswerReciever([&]()
    {
        // Wait arp message if not connected
        while (started) {
            char buffer[1024];
            memset(buffer, 0, sizeof buffer);

            struct sockaddr_in control_addr;
            socklen_t control_addr_len = sizeof(control_addr);

            ssize_t recvlen = recvfrom(recv_sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&control_addr, &control_addr_len);
            if (recvlen < 0) {
                perror("Failed to receive message");
                continue;
            }

            // Process message if it have preambula - "AMUR:"
            std::string message(buffer);
            std::string separator = ":";
            size_t pos = message.find(separator);
            if("OK" == message.substr(0, pos)){
                message.erase(0, pos + separator.length());
                int curGRPCPort = stoi(message.substr(0, message.find(separator)));

                // Находим или создаем клиента
                bool controlMachineFound = false;
                for (ControlMachine* control : controlMachineAddresses) {
                    if (control->address().sin_addr.s_addr == control_addr.sin_addr.s_addr) {
                        control->setLastSeen(std::chrono::system_clock::now());
                        controlMachineFound = true;
                        break;
                    }
                }
                if (!controlMachineFound) {
                    ControlMachine* control = new ControlMachine(control_addr, curGRPCPort);
                    control->setLastSeen(std::chrono::system_clock::now());
                    controlMachineAddresses.push_back(control);
                }
            }
        }
    });
    AnswerReciever.detach();

    return 0;
}

void Arper::stopArpingService()
{
    started = false;
    close(bcast_sockfd);
    close(recv_sockfd);
    std::cout << "[INFO] Arping service stopped" << std::endl;
}


std::chrono::system_clock::time_point ControlMachine::getLastSeen() const
{
    return last_seen;
}

void ControlMachine::setLastSeen(std::chrono::system_clock::time_point newLast_seen)
{
    last_seen = newLast_seen;
}

std::string ControlMachine::getIpAddr() const
{
    return ipAddr;
}

void ControlMachine::refreshIP()
{
    // obviously INET6_ADDRSTRLEN is expected to be larger
    // than INET_ADDRSTRLEN, but this may be required in case
    // if for some unexpected reason IPv6 is not supported, and
    // INET6_ADDRSTRLEN is defined as 0
    // but this is not very likely and I am aware of no cases of
    // this in practice (editor)
    char s[INET6_ADDRSTRLEN > INET_ADDRSTRLEN ? INET6_ADDRSTRLEN : INET_ADDRSTRLEN] = "\0";

    switch(m_address.sin_family) {
    case AF_INET:
        inet_ntop(AF_INET, &(m_address.sin_addr), s, INET_ADDRSTRLEN);
        break;

    case AF_INET6:
        inet_ntop(AF_INET, &(m_address.sin_addr), s, INET_ADDRSTRLEN);
        break;

    default:
        std::cerr << "Unknown AF" << std::endl;
    }

    ipAddr = s;
}

int ControlMachine::grpcPort() const
{
    return m_grpcPort;
}

void ControlMachine::setGrpcPort(int newGrpcPort)
{
    m_grpcPort = newGrpcPort;
}

sockaddr_in& ControlMachine::address()
{
    return m_address;
}

void ControlMachine::setAddress(const sockaddr_in &newAddress)
{
    m_address = newAddress;
}
