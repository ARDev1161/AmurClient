#ifndef GCLIENT_H
#define GCLIENT_H

#include <iostream>
#include <thread>
#include <chrono>

#include <grpcpp/grpcpp.h>

#include "protobuf/amur.grpc.pb.h"

class grpcClient
{
    std::unique_ptr<AMUR::ClientOnRobot::Stub> stub_;
    std::shared_ptr<grpc::Channel> clientChannel;

    AMUR::AmurSensors *sensors;
    AMUR::AmurControls *controls;

    bool stoppedStream = true;
    bool retryConnect;
    int retryDelayMilliseconds = 1000;

    std::mutex muClient;

 public:
    grpcClient(std::shared_ptr<grpc::Channel> channel, AMUR::AmurControls* controls, AMUR::AmurSensors* const sensors, bool tryConnectIfFailed = true);
    grpc::Status DataExchange();
    grpc::Status DataStreamExchange();
    void stopStream();
};

#endif // GCLIENT_H
