#ifndef NETWORKCONTROLLER_H
#define NETWORKCONTROLLER_H

#include <iostream>
#include <thread>

#include "client.h"
#include "server.h"

class NetworkController
{
    AMUR::AmurSensors *sensors;
    AMUR::AmurControls *controls;

    grpc::Status clientStatus;

    grpc::ServerBuilder builder;
    grpcServer service;

public:
    NetworkController(AMUR::AmurControls* const controls, AMUR::AmurSensors* const sensors);

    int runClient(std::string server_address); // Server address for client
    int runClient(std::string client_ip, unsigned int port); // Server address for client

    int runServer(std::string address_mask); // Address mask & port for server
    int runServer(std::string server_ip, unsigned int port); // Address mask & port for server
};

#endif // NETWORKCONTROLLER_H
