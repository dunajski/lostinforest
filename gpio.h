#ifndef GPIO_H
#define GPIO_H

#include "types.h"

//////////
// PINS //
//////////
// PORT A 
#define CS1   4
#define MISO1 6
#define MOSI1 7
#define SCK1  5

#define B1    0 // Blue Button named B1, PA0
// PORT B 
#define TX1 6
#define RX1 7
// PORT C 
#define LED3 9 // LED named LED3, PC9

typedef enum
{
  _INPUT  =    0x0UL,
  _OUTPUT =    0x1UL,
  _ALTERNATE = 0x2UL,
  _ANALOG =    0x3UL,
} EGpioType;

typedef enum
{
  _LOW_SPEED  = 0x0UL, // 2 MHz
  _MID_SPEED  = 0x1UL, // 10 MHz
  _HIGH_SPEED = 0x3UL, // 50 MHz
} EGpioSpeed;

typedef enum
{
  _NO_PUPD = 0x0UL, // no pull-up or pull-down
  _PU      = 0x1UL, // pull-up
  _PD      = 0x2UL, // pull-down
} EGpioPuPd;

typedef enum
{
  _PUSHPULL = 0x1UL,
  _OPENDRAIN = 0x1UL,
} EGpioPuPdOd;

// Gpio Type macros, MODER related
#define SetGpioMode(_PORT, _PIN, _TYPE) (_PORT->MODER = (volatile uint32)((_PORT->MODER & (~(0x3UL << (_PIN << 1)))) | (_PORT->MODER | (_TYPE << (_PIN << 1)))))
#define SetGpioAsAlternate(_PORT, _PIN) (SetGpioMode(_PORT, _PIN, _ALTERNATE))
#define SetGpioAsAnalog(_PORT, _PIN)    (SetGpioMode(_PORT, _PIN, _ANALOG))
#define SetGpioAsInput(_PORT, _PIN)     (SetGpioMode(_PORT, _PIN, _INPUT))
#define SetGpioAsOutput(_PORT, _PIN)    (SetGpioMode(_PORT, _PIN, _OUTPUT))

// Gpio Speed  macros, OSPEEDR related
#define SetGpioSpeed(_PORT, _PIN, _SPEED) (_PORT->OSPEEDR = (volatile uint32)((_PORT->OSPEEDR & (~(0x3UL << (_PIN << 1)))) | (_PORT->OSPEEDR | (_SPEED<< (_PIN << 1)))))
#define SetGpioToLowSpeed(_PORT, _PIN)     (SetGpioSpeed(_PORT, _PIN, _LOW_SPEED))
#define SetGpioToMidSpeed(_PORT, _PIN)     (SetGpioSpeed(_PORT, _PIN, _MID_SPEED))
#define SetGpioToHighSpeed(_PORT, _PIN)    (SetGpioSpeed(_PORT, _PIN, _HIGH_SPEED))

// Gpio pull-up/pull-down macros, PUPDR related
#define SetGpioPuPd(_PORT, _PIN, _PUPDTYPE) (_PORT->PUPDR = (volatile uint32)((_PORT->PUPDR & (~(0x3UL << (_PIN << 1)))) | (_PORT->PUPDR | (_PUPDTYPE << (_PIN << 1)))))
#define SetGpioPu(_PORT, _PIN) (SetGpioPuPd(_PORT, _PIN, _PU))
#define SetGpioPd(_PORT, _PIN)    (SetGpioPuPd(_PORT, _PIN, _PD))
#define SetGpioNoPuPd(_PORT, _PIN)     (SetGpioPuPd(_PORT, _PIN, _NO_PUPD))

#define SetGpioAsPushPull(_PORT, _PIN) (_PORT->OTYPER) = (volatile uint32)(_PORT->OTYPER & (~(_PUSHPULL << _PIN))
#define SetGpioAsOpenDrain(_PORT, _PIN) (_PORT->OTYPER) = (volatile uint32)(_PORT->OTYPER | _OPENDRAIN << _PIN)

#define EnablePortGpio(PORT_LETTER)  (RCC->AHBENR |= RCC_AHBENR_GPIO##PORT_LETTER##EN)
#define DisablePortGpio(PORT_LETTER)  (RCC->AHBENR &= (~RCC_AHBENR_GPIO##PORT_LETTER##EN))

#endif
