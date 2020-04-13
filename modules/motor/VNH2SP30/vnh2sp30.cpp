#include "vnh2sp30.h"

void setup(){
  pinMode(INA, OUTPUT);   
  pinMode(INB, OUTPUT);  
  pinMode(EN, OUTPUT);   

  digitalWrite(EN, HIGH);
}

void loop()
{
     digitalWrite(INA, LOW);      // крутим мотор в одну сторону
     digitalWrite(INB, HIGH);    
     analogWrite(PWM,motorSpeed);  
     delay(1000);
     
     digitalWrite(INA, HIGH);    // крутим мотор в противоположную сторону
     digitalWrite(INB, LOW);
     analogWrite(PWM, motorSpeed);  
     delay(1000);
     
     digitalWrite(EN, LOW);     // выключаем
     delay(1000);
     digitalWrite(EN, HIGH);
      
}  


void Temperature::setTempCPU(float temp){
    tempCPU = temp;
}
void Temperature::setTempAccelerometer(float temp){
    tempAccelerometer = temp;
}
void Temperature::setTempPressure(float temp){
    tempPressure = temp;
}

float Temperature::getTempCPU(){
    return tempCPU;
}
float Temperature::getTempAccelerometer(){
    return tempAccelerometer;
}
float Temperature::getTempPressure(){
    return tempPressure;
}
