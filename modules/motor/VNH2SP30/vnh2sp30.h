#ifndef VNH2SP30_H
#define VNH2SP30_H

#define INA 3     // выходы arduino
#define INB 4 
#define EN 2
#define PWM 6

class VNH2SP30
{
    int motorSpeed = 255; //  скорость мотора
public:
    void setTempCPU(float temp);
    void setTempAccelerometer(float temp);
    void setTempPressure(float temp);
    
    float getTempCPU();
    float getTempAccelerometer();
    float getTempPressure();
};

#endif // VNH2SP30_H
 

