#include <iostream>
#include "networkcontroller.h"

//#define GSERVER
#define GCLIENT

int main()
{
    AMUR::AmurControls controls;
    AMUR::AmurSensors sensors;

    NetworkController controller(&controls, &sensors);

#ifdef GSERVER
    std::cout << "Start server" << std::endl;
    controller.runServer("0.0.0.0:50051");
#endif

#ifdef GCLIENT
    std::cout << "Start client" << std::endl;
    sensors.mutable_temperature()->set_tempcpu(420) ;
    controller.runClient("localhost:50051");
#endif

    while(1);

    return 0;
}
