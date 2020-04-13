# Amur Client for RaspberryPi
This is application for communicate with robot on RPi base with [AmurClient].

## Requirements:
  1) WiringPi
  2) Protobuf
  3) libconfig

## Sensors of Amur:
  1) Camera - OV5647
  2) Inertial sensor - MPU-9250
  3) Barometer - BMP-280
  4) Encoders wheel: left, right
  5) Encoders hand internal: left, right
  6) Encoders hand outter: left, right
  7) Battery voltage

## Controls of Amur:
  1) ServoX, ServoY - MG90S
  2) Motor wheel: left, right
  3) Motor hand internal: left, right
  4) Motor hand outter: left, right

## GPIO using:
  GPIO4   -   Data from 74HC165
  GPIO17  -   Clk 74HC165
  GPIO18  -   Not master reset 74HC595
  GPIO27  -   SH/Not(LD) 74HC165
  GPIO22  -   Clk inh 74HC165
  GPIO23  -   Data to 74HC595
  GPIO24  -   SHcp 74HC595
  GPIO25  -   STcp 74HC595
  GPIO5   -   freePin 3
  GPIO6   -   freePin 4
  GPIO12  -   PWM1 right
  GPIO13  -   PWM1 left
  GPIO19  -   freePin 1
  GPIO16  -   Not OE 74HC595
  GPIO26  -   freePin 2
  GPIO20  -   PWM2 right
  GPIO21  -   PWM2 left
  
  I2C1    -   sensors: ADS1115
  
  UART0   -   sensors
  
  SPI0    -   LoRa: SX1278
  
## 74HC595 using:
  (First byte - right)
  1bit    -   right relay
  2bit    -   clk2 right motor shield
  3bit    -   clk1 right motor shield
  4bit    -   cnt1 right motor shield
  5bit    -   cnt2 right motor shield
  6bit    -   en1 right motor shield
  7bit    -   en2 right motor shield
  8bit    -   freeOutPinR

  (Second byte - left)
  9bit    -   left relay
  10bit   -   clk2 left motor shield
  11bit   -   clk1 left motor shield
  12bit   -   cnt1 left motor shield
  13bit   -   cnt2 left motor shield
  14bit   -   en1 left motor shield
  15bit   -   en2 left motor shield
  16bit   -   freeOutPinL
  
## 74HC165 using:
  1bit    -   LR2B encoder
  2bit    -   LR1B encoder
  3bit    -   LL2B encoder
  4bit    -   LL1B encoder
  5bit    -   LL1A encoder
  6bit    -   LL2A encoder
  7bit    -   LR1A encoder
  8bit    -   LR2A encoder

  9bit    -   freeInPin
  10bit   -   freeInPin
  11bit   -   freeInPin
  12bit   -   freeInPin
  13bit   -   R1A encoder
  14bit   -   R1B encoder
  15bit   -   R2B encoder
  16bit   -   R2A encoder

[AmurClient]:https://github.com/ARDev1161/AmurClient
