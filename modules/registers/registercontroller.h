#ifndef REGISTERCONTROLLER_H
#define REGISTERCONTROLLER_H

#include <hc595/hc595.h>
#include <hc165/hc165.h>

#include <stdio.h>

#define   SDI   0   //595 serial data input
#define   RCLK  1   //595 latch clock input(STcp)
#define   SRCLK 2   //595 data clock input(SHcp)
#define   NRESET 3   //595 not reset input(Not MR)
#define   NENABLE 4   //595 not enable input(Not OE)

unsigned char LED[8] = {0x01,0x02,0x04,0x08,0x10,0x20,0x40,0x80}; 

class registerController
{
    
public:
    registerController(int dataPin, int clkPin, int latchPin);
    void sendByte(unsigned char byte);
    void latchSignal();
};

#endif // REGISTERCONTROLLER_H
