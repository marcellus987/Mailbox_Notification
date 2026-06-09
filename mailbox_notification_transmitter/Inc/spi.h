#ifndef SPI_H__
#define SPI_H__

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"



void spi_pin_config(void);
void disable_spi(uint8_t disable_clock);
void spi_init(void);
void spi_disable(void);
void set_baudrate(uint8_t bd);
void spi_transmit(const uint8_t* data, uint32_t size);
void spi_receive(uint8_t* buffer, uint32_t size);
void slave_select(uint8_t pin_pos);
void slave_deselect(uint8_t pin_pos);

#endif /* SPI_H__ */
