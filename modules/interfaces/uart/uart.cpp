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
#if __has_include(<pigpio.h>)
   
#else
    std::cout << "UART initializing" << std::endl ;
    return 0;
#endif
}
