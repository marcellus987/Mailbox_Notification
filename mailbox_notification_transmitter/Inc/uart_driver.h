#ifndef UART_DRIVER_H__
#define UART_DRIVER_H__

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"

void uart_init(uint8_t USB_to_UART);
void uart_send(uint8_t *data, uint32_t len);
void uart_receive(uint8_t *buffer, uint32_t len);
void setBaudrate(uint32_t br);
#endif /* UART_DRIVER_H__ */
