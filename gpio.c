/*
 * Module to manage GPIO.
 */

#include "types.h"
#include "gpio.h"
#include "stm32f030x8.h"

/*
 *  Enables Clock for specified Port
 */
void EnableGpioClock(EGpioPorts gpio_port)
{
  switch (gpio_port)
  {
    case GPIOA_PORT:
      RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
      break;
    case GPIOB_PORT:
      RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
      break;
    case GPIOC_PORT:
      RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
      break;
    case GPIOD_PORT:
      RCC->AHBENR |= RCC_AHBENR_GPIODEN;
      break;
    case GPIOF_PORT:
      RCC->AHBENR |= RCC_AHBENR_GPIOFEN;
      break;
    default:
      break;
  }
}
