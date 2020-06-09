// dnj

#include <stdint.h>

#include "stm32f030x8.h"
#include "gpio.h"
#include "types.h"

#define HSI_VALUE 8000000

int main(void)
{
  // turn on GPIO clocks
  EnableGpioClock(GPIOC_PORT);
  // SET GPIO as Push-Pull Output
  GPIOC->MODER = (GPIOC->MODER & (~GPIO_MODER_MODER0)) | (0 | (0x01 * GPIO_MODER_MODER9_0));

  SysTick_Config(HSI_VALUE - 1);

  while (1)
  {
  }

  return 0;
}

volatile uint32 isr_test;
void SysTick_Handler(void)
{

  if (!isr_test)
  {
    GPIOC->BSRR = (0 | GPIO_BSRR_BS_9);
    isr_test = 1;
  }
  else if (isr_test)
  {
    GPIOC->BSRR = (0 | GPIO_BSRR_BR_9);
    isr_test = 0;
  }
}