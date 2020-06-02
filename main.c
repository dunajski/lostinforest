// dnj

#include <stdint.h>

#include "stm32f030x8.h"
#include "types.h"
#include "gpio.h"

#define DELAY_TEST 300000

void Delay(volatile uint32 n)
{
  while (n > 0) n--;
}

int main(void)
{
  // turn on GPIO clocks
  EnableGpioClock(GPIOC_Port);
  // SET GPIO as Push-Pull Output
  GPIOC->MODER = (GPIOC->MODER & (~GPIO_MODER_MODER0)) | (0 | (0x01 * GPIO_MODER_MODER9_0));

  while (1)
  {
    GPIOC->BSRR = (0 | GPIO_BSRR_BS_9);
    Delay(DELAY_TEST);
    GPIOC->BSRR = (0 | GPIO_BSRR_BR_9);
    Delay(DELAY_TEST);
  }

  return 0;
}
