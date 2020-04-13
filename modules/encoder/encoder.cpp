#include "encoder.h"


Encoder::Encoder(int signalAPin, int signalBPin):
    signalA(signalAPin), signalB(signalBPin)
{
    pinMode(signalA, INPUT);
    pinMode(signalB, INPUT);
}

int Encoder::getSignalA() const
{
    return signalA;
}

int Encoder::getSignalB() const
{
    return signalB;
}

void Encoder::refreshData()
{

}
