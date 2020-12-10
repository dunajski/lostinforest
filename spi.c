/*
 * Module to maintain SPI communication
 * dnj
 */
#include "types.h"
#include "stm32f030x8.h"
#include "gpio.h"
#include "spi.h"

void SPIInit(void)
{
  // MISO PA6
  // MOSI PA7
  // SCK  PA5
  // CS   PA4
  EnableGpioClock(GPIOA_PORT);

  GPIOA->MODER &= (~GPIO_MODER_MODER5_0);
  GPIOA->MODER |= (GPIO_MODER_MODER5_1);
  
  GPIOA->MODER &= (~GPIO_MODER_MODER6_0);
  GPIOA->MODER |= (GPIO_MODER_MODER6_1);

  GPIOA->MODER &= (~GPIO_MODER_MODER7_0);
  GPIOA->MODER |= (GPIO_MODER_MODER7_1);

  // TODO, check what is better use as AF or change state manually.
  GPIOA->MODER |= (GPIO_MODER_MODER4_0);

  // TODO consider that all GPIOs need fast speed?
  GPIOA->OSPEEDR = 0xffffffff;
  
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

  // BR b010, fpclk / 8 
  SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_BR_1 | SPI_CR1_SSM | SPI_CR1_CPOL | SPI_CR1_CPHA;
  SPI1->CR2 = SPI_CR2_FRXTH | SPI_CR2_DS_0 | SPI_CR2_DS_1 | SPI_CR2_DS_2 | SPI_CR2_SSOE | SPI_CR2_TXEIE | SPI_CR2_RXNEIE;

  SPI1->CR1 = SPI_CR1_SPE; // ENABLE SPI peripheral
}
