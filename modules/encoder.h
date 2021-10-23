#ifndef ENCODER_H
#define ENCODER_H

#include <chrono>
#include "peripheralsettings.h"

class Encoder
{
    const EncoderSettings *settings;

    std::chrono::high_resolution_clock::time_point lastUpdateTime; // Time from last run update()
    std::chrono::duration<double> timeSpan;

    double elapsedTime = 0;

    bool signalA;
    bool signalB;

    bool signalAPrev;
    bool signalBPrev;

    int angle;
    int angleStep;

    int angleSpeed;

public:
    Encoder(EncoderSettings *settings);
    ~Encoder();

    int update();

    int getEncoderAngle() const;
    void setEncoderAngle(int newAngle);

    // Returns the RPM
    int getRPM() const;

    void setSignalA(bool newSignalA);
    void setSignalB(bool newSignalB);

    unsigned int getSampleRate() const;
};

#endif // ENCODER_H
