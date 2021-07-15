#ifndef REGISTERSSETTINGS_H
#define REGISTERSSETTINGS_H

/*!
    \brief Структура для хранения параметров регистров

    Данная структура хранит набор пинов для управления регистрами в нотации GPIO и дополнительные настройки.
*/
struct RegisterSettings{
  /*!
      \brief Общие настройки регистров.

      Данная структура хранит общие настройки регистров.
  */
  struct General{
      const int usPulseDelay = 1;     // задержка импульса при изменении состояния пина GPIO
  } general;

  /*!
      \brief Структура для хранения пинов выходного регистра

      Данная структура хранит набор пинов Raspberry Pi для управления выходным регистром 74HC595 в нотации GPIO.
  */
  struct HC595Pins{
      const int dataPin = 23;      //595 serial data input
      const int latchClkPin = 25;  //595 latch clock input( STcp )
      const int clkPin = 24;       //595 data clock input( SHcp )
      const int nResetPin = 18;    //595 not reset input( Not MR )
      const int nEnablePin = 16;   //595 not enable input( Not OE )
  } hc595Pins;

  /*!
      \brief Структура для хранения пинов входного регистра

      Данная структура хранит набор пинов Raspberry Pi для управления входным регистром 74HC165 в нотации GPIO.
  */
  struct HC165Pins{
      const int dataPin = 4;             //165 serial data output
      const int clkPin = 17;             //165 data clock input
      const int clkInhibitePin = 22;     //165 inhibite clock input
      const int loadPin = 27;            //165 load register input( SH/Not(LD) )
  } hc165Pins;
};
#endif // REGISTERSSETTINGS_H
