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
  EnablePortGpio(A);

  SetGpioAsAlternate(GPIOA, MOSI1);
  SetGpioAsAlternate(GPIOA, MISO1);
  SetGpioAsAlternate(GPIOA, SCK1);
  // TODO, check what is better use as AF or change state manually.
  SetGpioAsOutput(GPIOA, CS1);

  // TODO consider that all GPIOs need fast speed?
  GPIOA->OSPEEDR = 0xffffffff;

  // no NEED to set AF registers, AF0 is fine.
  
  RCC->APB2ENR |= RCC_APB2ENR_SPI1EN;

  // SPI MASTER, BR b010, fpclk / 8 , fpclk == 8MHz??, SS software, HIGH in idle, 2edge latch
  SPI1->CR1 = SPI_CR1_MSTR | SPI_CR1_BR_1 | SPI_CR1_SSM | SPI_CR1_CPOL | SPI_CR1_CPHA;
  // interrupt after 8bit FIFO, 8bit, no need multimaster, TX/RX interrupts
  SPI1->CR2 = SPI_CR2_FRXTH | SPI_CR2_DS_0 | SPI_CR2_DS_1 | SPI_CR2_DS_2 | SPI_CR2_SSOE | SPI_CR2_TXEIE | SPI_CR2_RXNEIE;

  // TODO uncomment when sure how to use SPI ISRs
  // SPI1->CR1 = SPI_CR1_SPE; // ENABLE SPI peripheral
}

void SPI1_IRQHandler(void)
{
  // RX register not empty, something arrived
  if ((SPI1->SR & SPI_SR_RXNE) == SPI_SR_RXNE)
  {
    uchar rx_char;
    rx_char = (uchar)(SPI1->DR);
  }
    
  if ((SPI1->SR & SPI_SR_TXE) == SPI_SR_TXE)
  {
    // prepare sending here, i think there should be something more
    // than only this bit, why? right now it will gonna call this interrupt over
    // and over.
  }
}
