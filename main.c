// dnj

#include <stdint.h>

#include "stm32f030x8.h"
#include "types.h"

#define DELAY_TEST 300000

void Delay(volatile uint32 n)
{
  while (n > 0) n--;
}


int main(void)
{
  // turn on GPIO clocks
  RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
  // SET GPIO as Push-Pull Output
  GPIOC->MODER = (GPIOC->MODER & (~GPIO_MODER_MODER0)) | (0 | (0x01 * GPIO_MODER_MODER9_0));

  while (1)
  {
    GPIOC->BSRR = (0 | GPIO_BSRR_BS_9);
    Delay(DELAY_TEST);
    GPIOC->BSRR = (0 | GPIO_BSRR_BR_9);
    Delay(DELAY_TEST);
  }
}