#include "spi.h"

/*!
  Создаёт экземпляр класса для работы с интерфейсом I2C.
*/
SPI::SPI()
{

}

/*!
  Инициирует работу с интерфейсом SPI.
  \return Возвращает 0 если удалось открыть порт
*/
int SPI::init(){

    std::cout << "SPI initializing" << std::endl ;

#if __has_include(<wiringPiSPI.h>)


   // Configure the interface.
   // CHANNEL insicates chip select,
   // 500000 indicates bus speed.
   fd = wiringPiSPISetup(CHANNEL, 500000);

   std::cout << "Init result: " << fd << std::endl;

   // clear display
   buffer[0] = 0x76;
   wiringPiSPIDataRW(CHANNEL, buffer, 1);

   sleep(5);

   // Do a one-hot bit selection for each field of the display
   // It displays gibberish, but tells us that we're correctly addressing all
   // of the segments.
   for(int i = 1; i <= 0x7f; i <<= 1)
   {
      // the decimals, colon and apostrophe dots
      buffer[0] = 0x77;
      buffer[1] = i;
      result = wiringPiSPIDataRW(CHANNEL, buffer, 2);

      // The first character
      buffer[0] = 0x7b;
      buffer[1] = i;
      result = wiringPiSPIDataRW(CHANNEL, buffer, 2);

      // The second character
      buffer[0] = 0x7c;
      buffer[1] = i;
      result = wiringPiSPIDataRW(CHANNEL, buffer, 2);

      // The third character
      buffer[0] = 0x7d;
      buffer[1] = i;
      result = wiringPiSPIDataRW(CHANNEL, buffer, 2);

      // The last character
      buffer[0] = 0x7e;
      buffer[1] = i;
      result = wiringPiSPIDataRW(CHANNEL, buffer, 2);

      // Pause so we can see them
      sleep(5);
   }

   // clear display again
   buffer[0] = 0x76;
   wiringPiSPIDataRW(CHANNEL, buffer, 1);

#endif

}
