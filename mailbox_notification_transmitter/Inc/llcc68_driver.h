#ifndef LLCC68_DRVIER_H__
#define LLCC68_DRVIER_H__
#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"
#include "llcc68_defines.h"
#include "systick.h"
#include "spi.h"
#include "uart_driver.h"

/* Port A. */
#define NSS_PIN_POS 		(8U)

/* Port B. */
#define RFSW_V1_PIN_POS 	(0U)
#define RFSW_V2_PIN_POS 	(1U)
#define BUSY_PIN_POS 		(5U)
#define IRQ_PIN_POS 		(6U)
#define NRESET_PIN_POS		(8U)

/* Port C. */
#define USER_LED_PIN_POS 	(13U)


void LLCC68_init(void);




void readRegister(/*uint16_t address,*/ uint8_t* buffer);
void setRx(uint8_t *buffer);
void setTx(uint8_t *buffer, uint32_t len);


uint8_t getRSSI_Inst(void);
void getPacketStatus(uint8_t *result);


#endif /* LLCC68_DRVIER_H__ */
