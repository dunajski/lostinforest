// dnj
#include "stm32f030x8.h"
#include "gpio.h"
#include "types.h"

#define HSI_VALUE 8000000L // system_stm32f0xx.c

void UsartConfig(void);
void SendByteViaUart(uint8_t byte);

uint8_t stringtosend[] = {"TX WORKS\n"};

#define FIFO_SIZE 512
typedef struct
{
  uint16 ri;
  uint16 wi;
  uchar fifo[FIFO_SIZE];
} TCircularBuf;

TCircularBuf Input;
TCircularBuf Output;

void PutToSerial(uint8 * value, uint16 len)
{
  // fill circular buffer
  while (len--)
  {
    Output.fifo[Output.wi++] = *value++;
    if (Output.wi == FIFO_SIZE) Output.wi = 0;
  }
  // and send 1st byte
  USART1->TDR = Output.fifo[Output.ri++];
}

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

  PutToSerial(stringtosend, 10);
  while (1)
  {
  }

  return 0;
}

void SysTick_Handler(void)
{
}

void UsartConfig(void)
{
  EnableGpioClock(GPIOB_PORT);
  // Set PB6,PB7 as AF Gpio type
  GPIOB->MODER &= (~GPIO_MODER_MODER6_0);
  GPIOB->MODER |= (GPIO_MODER_MODER6_1);
  GPIOB->MODER &= (~GPIO_MODER_MODER7_0);
  GPIOB->MODER |= (GPIO_MODER_MODER7_1);
  // Set all gpios at max speed, don't care here
  GPIOB->OSPEEDR = 0xffffffff;

  RCC->APB2ENR |= RCC_APB2ENR_USART1EN; // Enable clock for USART1

  USART1->BRR = HSI_VALUE / 9600L; // Baud-rate

  USART1->CR1 |= USART_CR1_UE | USART_CR1_RE | USART_CR1_TE | USART_CR1_RXNEIE | USART_CR1_TCIE;
}


void USART1_IRQHandler(void)
{
  // RX register not empty (RXNE)
  if ((USART1->ISR & USART_ISR_RXNE) == USART_ISR_RXNE)
  {
    uchar rx_char;
    rx_char = (uchar)(USART1->RDR); /* Receive data, clear flag */

    if (rx_char == 'e') // enable LED
      GPIOC->BSRR = GPIO_BSRR_BS_9;
    else if (rx_char == 'd') // disable LED
      GPIOC->BSRR = GPIO_BSRR_BR_9;

    Input.fifo[Input.wi++] = rx_char;
    if (Input.wi == FIFO_SIZE) 
      Input.wi = 0;
  }

  // Transmission complete (TC)
  if ((USART1->ISR & USART_ISR_TC) == USART_ISR_TC)
  {
    USART1->ICR |= USART_ICR_TCCF;
    if (Output.ri != Output.wi)
    {
      USART1->TDR = Output.fifo[Output.ri++];
      if (Output.ri == FIFO_SIZE) Output.ri = 0; // move index to the begin
    }
  }
}
