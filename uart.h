#ifndef UART_H
#define UART_H

#include "types.h"

void UartConfig(void);
void PutToSerial(uint8 * value, uint16 len);

#endif
