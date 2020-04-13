#ifndef MOTORCONTROLLER_H
#define MOTORCONTROLLER_H

#include "VNH2SP30/vnh2sp30.h"

class MotorController
{
    VNH2SP30 wheelLeft; //Left wheel motor driver
    VNH2SP30 wheelRight; //Right wheel motor driver

    VNH2SP30 handLeft; //Left hand motor driver
    VNH2SP30 handRight; //Right hand motor driver

    int relayLeft = 0; //Relay left pin
    int relayRight = 0; //Relay right pin
    
    void setRelayLeft(int value);
    void setRelayRight(int value);
public:
    MotorController();
};

#endif // MOTORCONTROLLER_H
