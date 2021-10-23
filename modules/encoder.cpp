#include "encoder.h"

Encoder::Encoder(EncoderSettings *inSettings):
    settings(inSettings)
{
    angleStep = 360.0 / static_cast<double>(settings->encoderSectorsCount); // Compute angle step in degrees

    lastUpdateTime = std::chrono::high_resolution_clock::now();
    update();
}

Encoder::~Encoder()
{
    settings = nullptr;
}

int Encoder::update()
{
    auto curTime = std::chrono::high_resolution_clock::now(); // Update time stamp
    timeSpan = std::chrono::duration_cast<std::chrono::duration<double>>(curTime - lastUpdateTime);
    elapsedTime = timeSpan.count();

    if ((signalA != signalAPrev) || (signalB != signalBPrev))   // Encoder state change
    {
        if (signalA > signalB)
            angle += angleStep;

        if (signalA < signalB)
            angle -= angleStep;

        angle %= 180; // Translate angle to (-180;180) diapason

        angleSpeed = angleStep / elapsedTime; // Degrees/seconds
    }

    lastUpdateTime = curTime;

    return 0;
}

void Encoder::setSignalA(bool newSignalA)
{
    signalAPrev = signalA;
    signalA = newSignalA;
}

void Encoder::setSignalB(bool newSignalB)
{
    signalBPrev = signalB;
    signalB = newSignalB;
}

void Encoder::setEncoderAngle(int newAngle)
{
    angle = newAngle;
}

int Encoder::getEncoderAngle() const
{
    return angle;
}

int Encoder::getRPM() const
{
    return angleSpeed;
}

unsigned int Encoder::getSampleRate() const
{
    return settings->sampleRate;
}
