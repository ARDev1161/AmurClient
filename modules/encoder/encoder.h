#ifndef ENCODER_H
#define ENCODER_H

#include "wiringPi.h"

class Encoder
{
    int signalA = 0;
    int signalB = 0;

public:
    Encoder(int signalAPin, int signalBPin);

    int getSignalA() const;
    int getSignalB() const;
    void refreshData();
};

#endif // ENCODER_H
