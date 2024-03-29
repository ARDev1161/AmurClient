#include "server.h"

void grpcServer::setProtosPointers(AMUR::AmurControls *const controls, AMUR::AmurSensors *const sensors)
{
    this->controls = controls;
    this->sensors = sensors;
}

grpc::Status grpcServer::DataExchange ([[maybe_unused]] grpc::ServerContext* context,
                          const AMUR::AmurControls* request, AMUR::AmurSensors* reply)
{
  std::unique_lock<std::mutex> ul(muServer);
  *controls = *request;
  ul.unlock();

  *reply = *sensors;
  return grpc::Status::OK;
}

grpc::Status grpcServer::DataStreamExchange ([[maybe_unused]] grpc::ServerContext* context,
                                grpc::ServerReaderWriter<AMUR::AmurSensors, AMUR::AmurControls >* stream)
{
    std::unique_lock<std::mutex> ul(muServer, std::defer_lock);

    while(true)
    {
      ul.lock();
      if(!(stream->Read(controls)))
          return grpc::Status::OK;
      ul.unlock();

      // Write controls
      stream->Write(*sensors);
    }
}
