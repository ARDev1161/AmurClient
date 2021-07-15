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
#if __has_include(<pigpio.h>)

#else
    std::cout << "SPI initializing" << std::endl ;
    return 0;
#endif
}
