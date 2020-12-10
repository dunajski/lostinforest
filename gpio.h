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

// add new IO config when need
// definition A_B_C_D where:
// A - I/O, B - GI/GO/AF, C - PP/OD, D - NP/PU/PD.
// Example: O_GP_PP_NP
// check table of possible type for IO in reference manual
// naming taken from reference manual:
// GP = general-purpose,
// PP = push-pull,
// NP = no pull-up/down
// PU = pull-up,
// PD = pull-down,
// OD = open-drain,
// AF = alternate function.
// TODO, Consider is it worth a special type?
typedef enum
{
  O_GP_PP_NP = 0,
} EIoType;

void EnableGpioClock(EGpioPorts gpio_port);

#endif
