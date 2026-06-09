#ifndef IR_BEAM_DRIVER_H__
#define IR_BEAM_DRIVER_H__

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"


void ir_beam_init(void);
uint8_t check_sensor_status(void);

void ir_beam_on(void);
void ir_beam_off(void) ;

#endif /* IR_BEAM_DRIVER_H__ */
