// dnj

#include <stdint.h>

#include "stm32f030x8.h"
#include "gpio.h"
#include "types.h"

#define HSI_VALUE 8000000L
void UsartConfig(void);
void SendByteViaUart(uint8_t byte);

int i = 0;
uint8_t stringtosend[] = {"TX WORKS\n"};
uint8_t sent =0;

int main(void)
{
  // turn on GPIO clocks
  EnableGpioClock(GPIOC_PORT);
  // SET GPIO as Push-Pull Output
  GPIOC->MODER |= GPIO_MODER_MODER9_0;

  SysTick_Config(HSI_VALUE - 1);
  NVIC_EnableIRQ(USART1_IRQn);
  NVIC_SetPriority(USART1_IRQn, 0);
  UsartConfig();

  while (1)
  {
    if (sent)
    {
      sent = 0;
      SendByteViaUart(stringtosend[i++]);
    }
    if (i >= 9) i = 0;
  }

  return 0;
}

void SysTick_Handler(void)
{
}

void UsartConfig(void)
{
  EnableGpioClock(GPIOB_PORT);
  GPIOB->MODER &= (~GPIO_MODER_MODER6_0);
  GPIOB->MODER |= (GPIO_MODER_MODER6_1);
  GPIOB->MODER &= (~GPIO_MODER_MODER7_0);
  GPIOB->MODER |= (GPIO_MODER_MODER7_1);
  GPIOB->OSPEEDR = 0xffffffff;
  RCC->APB2ENR |= RCC_APB2ENR_USART1EN;

  USART1->BRR = HSI_VALUE / 9600L;
  USART1->CR1 |= USART_CR1_RXNEIE | USART_CR1_RE | USART_CR1_UE  | USART_CR1_TE | USART_CR1_TCIE;
}

char volatile chartoreceive;

void SendByteViaUart(uint8_t byte)
{
  USART1->TDR = byte;
}

void USART1_IRQHandler(void)
{
  if ((USART1->ISR & USART_ISR_RXNE) == USART_ISR_RXNE)
  {
    chartoreceive = (uint8_t)(USART1->RDR); /* Receive data, clear flag */

    if (chartoreceive == 'z')
      GPIOC->BSRR = (0 | GPIO_BSRR_BS_9);
    else if (chartoreceive == 'x')
      GPIOC->BSRR = (0 | GPIO_BSRR_BR_9);
  }

  // Byte was successfully sent
  if ((USART1->ISR & USART_ISR_TC) == USART_ISR_TC)
  {
    sent = 1;
    USART1->ICR |= USART_ICR_TCCF;
  }
}