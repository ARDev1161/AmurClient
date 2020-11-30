#ifndef GSERVER_H
#define GSERVER_H

#include <iostream>

#include <grpcpp/grpcpp.h>
#include <grpcpp/health_check_service_interface.h>
#include <grpcpp/ext/proto_server_reflection_plugin.h>

#include "protobuf/amur.grpc.pb.h"

// Logic and data behind the server's behavior.
class grpcServer final : public AMUR::Maintenance::Service
{
  AMUR::AmurControls *controls;
  AMUR::AmurSensors *sensors;
  std::mutex muServer;

  grpc::Status DataExchange([[maybe_unused]] grpc::ServerContext* context,
                            const AMUR::AmurSensors* request, AMUR::AmurControls* reply) override;

  grpc::Status DataStreamExchange([[maybe_unused]] grpc::ServerContext* context,
                                  grpc::ServerReaderWriter<AMUR::AmurControls, AMUR::AmurSensors>* stream) override;

public:
    void setProtosPointers(AMUR::AmurControls *const controls, AMUR::AmurSensors *const sensors);
    int checkConn();
};

#endif // GSERVER_H
