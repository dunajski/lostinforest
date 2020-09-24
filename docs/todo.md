### TODO List

1. ~~Add TODO List~~
2. Simple tasks to test makefile and renew coding skills with "bare-metal"
  - [x]blink led with HAL 
  - [x]blink led without HAL
  - [x]send few bytes via USART with HAL (didn't try, no needed)
  - [x]receive few bytes via UART without HAL
  - [x]send few bytes via USART without HAL
3. Choose "working" demo-board (task 2 can enormously help)
  * ~~Nucleo L073~~
  * ~~Nucleo F401RE with MCU STM32 F405 (soldered?)~~
  * ~~Discovery F030~~
4. Send few bytes with SPI/I2C (need in task 5)
  - [ ]choose one protocol
  - [ ]try to send something between two nucleos? 
5. Learn how to use LIS3DH
  - [ ]datasheets
  - [ ]examples (github etc.)
  - [ ]experimenting
6. Learn mathematics related to using sensor mentioned above
7. Test equations with some sample measurements
8. Interface with user

### tasks:
  1. EGpioType as full structure instead of enums - reason?  
  It's gonna be painful to add every combination when use new type,  
  matrix of possibilities.
  2. TX/RX UART full in interrupts.
