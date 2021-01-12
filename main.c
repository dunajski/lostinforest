/*
 * Lost in forest
 * dnj
 */
#include "stm32f030x8.h"
#include "gpio.h"
#include "types.h"
#include "uart.h"
#include "spi.h"

uchar stringtosend[] = {"TX WORKS\n"};
uint32 test;

int main(void)
{
  EnablePortGpio(C);
  SetGpioAsOutput(GPIOC, LED3);

  EnablePortGpio(A);
  SetGpioAsInput(GPIOA, B1);

  SysTick_Config(HSI_VALUE - 1);
  NVIC_EnableIRQ(USART1_IRQn);
  NVIC_SetPriority(USART1_IRQn, 0);
  NVIC_EnableIRQ(SPI1_IRQn);
  NVIC_SetPriority(SPI1_IRQn, 0);
  UARTInit();
  SPIInit();

  PutToSerial(stringtosend, 10);

  uint8_t button_down = 0;
  while (1)
  {
      uint32_t idr_val = GPIOA->IDR;
      test+=1;
      if (idr_val & GPIO_IDR_0)
      {
        // The button is pressed; if it was not already
        // pressed, change the LED state.
        if (!button_down)
          GPIOC->ODR ^= (GPIO_ODR_9);
        button_down = 1;
      }
      else
        button_down = 0;
  }

  return 0;
}

void SysTick_Handler(void)
{
}
