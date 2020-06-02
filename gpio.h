#ifndef GPIO_H
#define GPIO_H

#include "types.h"

typedef enum
{
  GPIOA_Port = 0,
  GPIOB_Port,
  GPIOC_Port,
  GPIOD_Port,
  GPIOF_Port,
} EGpioPorts;

void EnableGpioClock(EGpioPorts gpio_port);

#endif
