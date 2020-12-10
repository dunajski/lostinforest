#ifndef UART_H
#define UART_H

#include "types.h"

void UARTInit(void);
void PutToSerial(uint8 * value, uint16 len);

#endif
