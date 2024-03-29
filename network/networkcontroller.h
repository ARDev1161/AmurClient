#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include <iostream>
#include <thread>

#include "client.h"
#include "server.h"
#include "arper.h"

class NetworkController
{
    AMUR::AmurSensors *sensors;
    AMUR::AmurControls *controls;

    grpc::Status clientStatus;

    bool connected = false;

    Arper *arpService;

    grpc::ServerBuilder builder;
    grpcServer service;

    std::vector<ControlMachine*> controlMachineAddresses;
    std::vector<ControlMachine*> verified;
public:
    NetworkController(AMUR::AmurControls* const controls, AMUR::AmurSensors* const sensors);

    int startArpingService(int bcastPort, int arpingPort = 0);
    void stopArpingService();

    int runClient(std::string &server_address, bool tryConnectIfFailed = true); // Server address & port for client
    int runClient(bool tryConnectToUnverified = true); // Server address & port for client

    int runServer(std::string &address_mask); // Address mask & port for server
};

#endif // NETWORKCONTROLLER_H
