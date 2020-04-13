#ifndef LOGICCONTROLLER_H
#define LOGICCONTROLLER_H

//Protobuf headers
#include "protobuf/control.pb.h"
#include "protobuf/sensors.pb.h"

//Peripheral controller header
#include "modules/peripheralcontroller.h"

//Network headers

class LogicController
{
    AmurSensors *sensors;
    AmurControls *controls;

    PeripheralController *periphery;
public:
    LogicController();

    void writeToPeriphery();
    void readFromPeriphery();
};

#endif // LOGICCONTROLLER_H
