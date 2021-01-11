#ifndef GPIO_H
#define GPIO_H

#include "types.h"

typedef enum
{
  GPIOA_PORT = 0,
  GPIOB_PORT,
  GPIOC_PORT,
  GPIOD_PORT,
  GPIOF_PORT,
} EGpioPorts;

void EnableGpioClock(EGpioPorts gpio_port);

typedef enum
{
  _INPUT  =    0x00,
  _OUTPUT =    0x01,
  _ALTERNATE = 0x02,
  _ANALOG =    0x03,
} EGpioType;

#define SetGpioMode(PORT, PIN, TYPE) (PORT->MODER = (volatile uint32)((PORT->MODER & (~(0x03 << (PIN * 2)) | (PORT->MODER | (TYPE << (PIN * 2))))
#define SetGpioAsAlternate(PORT, PIN) (SetGpioMode(PORT, PIN, _ALTERNATE))
#define SetGpioAsAnalog(PORT, PIN)    (SetGpioMode(PORT, PIN, _ANALOG))
#define SetGpioAsInput(PORT, PIN)     (SetGpioMode(PORT, PIN, _INPUT))
#define SetGpioAsOutput(PORT, PIN)    (SetGpioMode(PORT, PIN, _OUTPUT))

#endif
