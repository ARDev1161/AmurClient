#include "client.h"

grpcClient::grpcClient(std::shared_ptr<grpc::Channel> channel, AMUR::AmurControls* controls, AMUR::AmurSensors * const sensors, bool tryConnectIfFailed)
    : stub_(AMUR::ClientOnRobot::NewStub(channel)),
      retryConnect(tryConnectIfFailed)
{
    clientChannel = channel;
    this->controls = controls;
    this->sensors = sensors;
}

// Assembles the client's payload, sends it and presents the response back from the server.
grpc::Status grpcClient::DataExchange()
{
    grpc::Status status;
    bool retry = true; // Flag that defined need connectiong retry or no

    while(retry){
        // Container for the data we expect from the server.
        AMUR::AmurControls reply;

        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        grpc::ClientContext context;

        // The actual RPC.
        status = stub_->DataExchange(&context, *sensors, &reply);

        std::unique_lock<std::mutex> ul(muClient);

        // Act upon its status.
        if (status.ok()){
          *controls = reply;
          retry = false;
        }
        else{
          std::cout << "DataExchange rpc failed!" << std::endl;
          std::this_thread::sleep_for(std::chrono::milliseconds( retryDelayMilliseconds ));
        }

    }

    return status;
}

void grpcClient::stopStream()
{
    stoppedStream = true;
}

grpc::Status grpcClient::DataStreamExchange()
{
    grpc::Status status;
    bool retry = true;
    stoppedStream = false;

    while(retry){
        // Context for the client. It could be used to convey extra information to
        // the server and/or tweak certain RPC behaviors.
        grpc::ClientContext context;

        std::shared_ptr<grpc::ClientReaderWriter<AMUR::AmurSensors, AMUR::AmurControls> > stream(
            stub_->DataStreamExchange(&context));

        while(!stoppedStream && (clientChannel->GetState(true) == 2) )
        {
            // Write sensors
            stream->Write(*sensors);

            std::unique_lock<std::mutex> lock(muClient);

            // Read controls & write to protos
            stream->Read(controls);
        }

        stream->WritesDone();

        status = stream->Finish();
        if (status.ok())
            retry = false;
        else {
            std::cout << "Error " << status.error_code() << " : " << status.error_message() << std::endl;
            std::cout << "DataStreamExchange rpc failed." << std::endl;
            std::this_thread::sleep_for(std::chrono::milliseconds( retryDelayMilliseconds ));
        }

    }

    stoppedStream = false;

    return status;
}
