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
    case GPIOA_Port:
      RCC->AHBENR |= RCC_AHBENR_GPIOAEN;
      break;
    case GPIOB_Port:
      RCC->AHBENR |= RCC_AHBENR_GPIOBEN;
      break;
    case GPIOC_Port:
      RCC->AHBENR |= RCC_AHBENR_GPIOCEN;
      break;
    case GPIOD_Port:
      RCC->AHBENR |= RCC_AHBENR_GPIODEN;
      break;
    case GPIOF_Port:
      RCC->AHBENR |= RCC_AHBENR_GPIOFEN;
      break;
    default:
      break;
  }
}
