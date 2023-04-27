#include "networkcontroller.h"


NetworkController::NetworkController(AMUR::AmurControls* const controls, AMUR::AmurSensors* const sensors)
{
    this->controls = controls;
    this->sensors = sensors;
}

int NetworkController::startArpingService(int bcastPort, int arpingPort)
{
    if(!arpService)
        arpService = new Arper(controlMachineAddresses, bcastPort, arpingPort);

    return arpService->startArpingService(connected);
}

void NetworkController::stopArpingService()
{
    arpService->stopArpingService();
}

int NetworkController::runClient(std::string &server_address, bool tryConnectIfFailed)
{
    // Instantiate the client. It requires a channel, out of which the actual RPCs
    // are created. This channel models a connection to an endpoint specified by
    // the argument "--target=" which is the only expected argument.
    // We indicate that the channel isn't authenticated (use of
    // InsecureChannelCredentials()).

    std::thread thr([&, server_address]()
     {
        // TODO get server address from controlMachineAddresses
        grpcClient client(grpc::CreateChannel(
            server_address, grpc::InsecureChannelCredentials()), controls, sensors);

        clientStatus = client.DataStreamExchange();
//        std::cout << "State is OK?: " << clientStatus.ok() << std::endl;
        if(clientStatus.ok())
            connected = true;
     }
    );
    thr.detach();

    return 0;
}

int NetworkController::runClient(bool tryConnectToUnverified)
{
    if(controlMachineAddresses.empty())
        return -1;

    ControlMachine *cur = controlMachineAddresses[0];
    std::string curAddr = cur->getIpAddr();
    controlMachineAddresses.erase( controlMachineAddresses.begin() );

    if(curAddr == "\0")
        return -2;

    curAddr += ":" + std::to_string(cur->grpcPort());

    return runClient(curAddr, true);
}

int NetworkController::runServer(std::string &address_mask)
{
    std::thread thr([&]()
     {
      grpc::EnableDefaultHealthCheckService(true);
      grpc::reflection::InitProtoReflectionServerBuilderPlugin();

      // Send protos pointers to server
      service.setProtosPointers(controls, sensors);

      // Listen on the given address without any authentication mechanism.
      builder.AddListeningPort(address_mask, grpc::InsecureServerCredentials());

      // Register "service" as the instance through which we'll communicate with
      // clients. In this case it corresponds to an *synchronous* service.
      builder.RegisterService(&service);

      // Finally assemble the server.
      std::unique_ptr<grpc::Server> server(builder.BuildAndStart());
      std::cout << "Server listening on " << address_mask << std::endl;

      // Wait for the server to shutdown. Note that some other thread must be
      // responsible for shutting down the server for this call to ever return.
      server->Wait();

      std::cout << "Server stopped " << std::endl;
     }
    );
    thr.detach();

    return 0;
}
