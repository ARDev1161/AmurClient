#include "registercontroller.h"

int wiringInit(){
    if(wiringPiSetupGpio() != 0) //setup GPIO, this uses actual BCM pin numbers 
	{ 
        printf("setup wiringPi failed !");
        return 1;
    } 
}

    
