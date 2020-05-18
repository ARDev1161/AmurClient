#include "uart.h"

/*!
  Создаёт экземпляр класса для работы с интерфейсом UART.
*/
UART::UART()
{

}

/*!
  Инициирует работу с интерфейсом UART.
  \return Возвращает 0 если удалось открыть порт
*/
int UART::init()
{

#if __has_include(<wiringPi.h>)
    int fd ;
    int count ;
    unsigned int nextTime ;

    if ((fd = serialOpen ("/dev/ttyAMA0", 115200)) < 0)
    {
      fprintf (stderr, "Unable to open serial device: %s\n", strerror (errno)) ;
      return 1 ;
    }

    if (wiringPiSetup () == -1)
    {
          fprintf (stdout, "Unable to start wiringPi: %s\n", strerror (errno)) ;
          return 1 ;
    }
    nextTime = millis () + 300 ;

    for (count = 0 ; count < 256 ; )
    {
      if (millis () > nextTime)
      {
        printf ("\nOut: %3d: ", count) ;
        fflush (stdout) ;
        serialPutchar (fd, count) ;
        nextTime += 300 ;
        ++count ;
      }

      std::this_thread::sleep_for(std::chrono::milliseconds(3));

      while (serialDataAvail (fd))
      {
        printf (" -> %3d", serialGetchar (fd)) ;
        fflush (stdout) ;
      }
    }
#else
    std::cout << "UART initializing" << std::endl ;
    return 0;
#endif

}
