#include "i2c.h"

/*!
  Создаёт экземпляр класса для работы с интерфейсом I2C.
*/
I2C::I2C()
{
}

void I2C::init(){
}

void I2C::parse_I2C(int SCL, int SDA)
{
   static int in_data=0, byte=0, bit=0;
   static int oldSCL=1, oldSDA=1;

   int xSCL, xSDA;

   if (SCL != oldSCL)
   {
      oldSCL = SCL;
      if (SCL) xSCL = SCL_RISING;
      else     xSCL = SCL_FALLING;
   }
   else        xSCL = SCL_STEADY;

   if (SDA != oldSDA)
   {
      oldSDA = SDA;
      if (SDA) xSDA = SDA_RISING;
      else     xSDA = SDA_FALLING;
   }
   else        xSDA = SDA_STEADY;

   switch (xSCL+xSDA)
   {
      case SCL_RISING + SDA_RISING:
      case SCL_RISING + SDA_FALLING:
      case SCL_RISING + SDA_STEADY:
         if (in_data)
         {
            if (bit++ < 8)
            {
               byte <<= 1;
               byte |= SDA;
            }
            else
            {
               printf("%02X", byte);
               if (SDA) printf("-"); else printf("+");
               bit = 0;
               byte = 0;
            }
         }
         break;

      case SCL_FALLING + SDA_RISING:
         break;

      case SCL_FALLING + SDA_FALLING:
         break;

      case SCL_FALLING + SDA_STEADY:
         break;

      case SCL_STEADY + SDA_RISING:
         if (SCL)
         {
            in_data = 0;
            byte = 0;
            bit = 0;

            printf("]\n"); // stop
            fflush(NULL);
         }
         break;

      case SCL_STEADY + SDA_FALLING:
         if (SCL)
         {
            in_data = 1;
            byte = 0;
            bit = 0;

            printf("["); // start
         }
         break;

      case SCL_STEADY + SDA_STEADY:
         break;

   }
}

int I2C::scanBus(int gSCL, int gSDA)
{
    uint32_t level, changed, bI2C, bSCL, bSDA;

#if __has_include(<pigpio.h>)
    gpioReport_t report;

    bSCL = 1<<gSCL;
    bSDA = 1<<gSDA;

    bI2C = bSCL | bSDA;

    /* default to SCL/SDA high */

    SCL = 1;
    SDA = 1;
    level = bI2C;

    while ((r=read(STDIN_FILENO, &report, RS)) == RS)
    {
       report.level &= bI2C;

       if (report.level != level)
       {
          changed = report.level ^ level;

          level = report.level;

          if (level & bSCL) SCL = 1; else SCL = 0;
          if (level & bSDA) SDA = 1; else SDA = 0;

          parse_I2C(SCL, SDA);
       }
    }
#endif

    return 0;
}

