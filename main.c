/*
 * Lost in forest
 * dnj
 */
#include "stm32f030x8.h"
#include "gpio.h"
#include "types.h"
#include "uart.h"

uchar stringtosend[] = {"TX WORKS\n"};

int main(void)
{
  // turn on GPIO clocks
  EnableGpioClock(GPIOC_PORT);
  // SET GPIO as Push-Pull Output
  GPIOC->MODER |= GPIO_MODER_MODER9_0;

  SysTick_Config(HSI_VALUE - 1);
  NVIC_EnableIRQ(USART1_IRQn);
  NVIC_SetPriority(USART1_IRQn, 0);
  UartConfig();

  PutToSerial(stringtosend, 10);
  while (1)
  {
  }

  return 0;
}

void SysTick_Handler(void)
{
}
