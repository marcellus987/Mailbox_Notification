#include "llcc68_driver.h"

#define READ_CMD_OPCODE 0x1D

#define SCLCK_PIN_POS 	(5U)
#define MISO_PIN_POS	(6U)
#define MOSI_PIN_POS 	(7U)

static void sendCommand(uint8_t opCode, uint8_t *args, uint32_t argCount) {
	while(GPIOB->IDR & (1U << BUSY_PIN_POS)) {
		/* For some unknown reason, this causes bug. UART's TC bit never sets. */
//		printf("Chip is busy...\r\n");
//		uint8_t text[] = "Chip is busy";
//		uint8_t len = sizeof(text);
//		uart_send(&len, 1);
//		uart_send(text, len);
	}
	spi_transmit(&opCode, 1);

	if(args != NULL) {
		spi_transmit(args, argCount);
	}
}

static void configureCommonParams(void) {
	/* 1: Set to Stand-by. */
	slave_select(NSS_PIN_POS);
	uint8_t cmd = LLCC68_CMD_SET_STANDBY;
	uint8_t args[] = {0x00};
	sendCommand(cmd, args, sizeof(args));
	slave_deselect(NSS_PIN_POS);

	/* 2: Set packet type. */
	slave_select(NSS_PIN_POS);
	cmd = LLCC68_CMD_SET_PACKET_TYPE;
	uint8_t args2[] = {0x00};
	sendCommand(cmd, args2, sizeof(args2));
	slave_deselect(NSS_PIN_POS);

	/* 3: Set RF Frequency. */
	slave_select(NSS_PIN_POS);
	cmd = LLCC68_CMD_SET_RF_FREQUENCY;
	uint8_t args3[] = {0x39, 0x30, 0x00, 0x00};
	sendCommand(cmd, args3, sizeof(args3));
	slave_deselect(NSS_PIN_POS);

	/* 4: Set Buffer base address. */
	slave_select(NSS_PIN_POS);
	cmd = LLCC68_CMD_SET_BUFFER_BASE_ADDRESS;
	uint8_t args4[] = {0x00, 0x80};
	sendCommand(cmd, args4, sizeof(args4));
	slave_deselect(NSS_PIN_POS);

	/* 5: Set Modulation params. */
	slave_select(NSS_PIN_POS);
	cmd = LLCC68_CMD_SET_MODULATION_PARAMS;
	uint8_t args5[] = {0x03, 0x41, 0x55, 0x09, 0x0C, 0x00, 0x14, 0x7B};
	sendCommand(cmd, args5, sizeof(args5));
	slave_deselect(NSS_PIN_POS);

	/* 6: Set Sync word value. */
	slave_select(NSS_PIN_POS);
	cmd = LLCC68_CMD_WRITE_REGISTER;
	uint8_t args8[] = {0x06, 0xC0, 0x01, 0x02, 0x03};
	sendCommand(cmd, args8, sizeof(args8));
	slave_deselect(NSS_PIN_POS);
}


void LLCC68_pin_config(void) {
	/* Enable clock for GPIOA and GPIOB. */
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;

	/* Reset mode configurations for port A. */
	GPIOA->MODER &= ~GPIO_MODER_MODER8_Msk;

	/* Reset mode configurations for port B. */
	GPIOB->MODER &= ~(GPIO_MODER_MODER0_Msk | GPIO_MODER_MODER1_Msk | GPIO_MODER_MODER5_Msk | GPIO_MODER_MODER6_Msk| GPIO_MODER_MODER8_Msk);

	/* Configure output mode for port A pin. */
	GPIOA->MODER |= GPIO_MODER_MODER8_0;
}


void LLCC68_init(void) {
	spi_init();
	LLCC68_pin_config();
	slave_deselect(NSS_PIN_POS);

	/* Configure common parameters. */
	configureCommonParams();
}

void readRegister(/*uint16_t address,*/ uint8_t* buffer) {

}


//static void configureRxParams(void) {
//	/* 1: Set Packet params. */
//	slave_select(NSS_PIN_POS);
//	cmd = LLCC68_CMD_SET_PACKET_PARAMS;
//	uint8_t args6[] = {0x00, 0x20, 0x04, 0x18, 0x00, 0x01, 0xFF, 0x02, 0x01};
//	sendCommand(cmd, args6, sizeof(args6));
//	slave_deselect(NSS_PIN_POS);
//
//	/* 2: Set DioIrqParams. */
//	slave_select(NSS_PIN_POS);
//	cmd = LLCC68_CMD_SET_DIO_IRQ_PARAMS;
//	uint8_t args7[] = {0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00};
//	sendCommand(cmd, args7, sizeof(args7));
//	slave_deselect(NSS_PIN_POS);
//}



void setRx(uint8_t *buffer) {
	uint8_t cmd;
//	/* 1: Set Rx to Stand-by. */
//	slave_select(NSS_PIN_POS);
//	uint8_t cmd = LLCC68_CMD_SET_STANDBY;
//	uint8_t args[] = {0x00};
//	sendCommand(cmd, args, sizeof(args));
//	slave_deselect(NSS_PIN_POS);

//	/* 2: Set packet type. */
//	slave_select(NSS_PIN_POS);
//	cmd = LLCC68_CMD_SET_PACKET_TYPE;
//	uint8_t args2[] = {0x00};
//	sendCommand(cmd, args2, sizeof(args2));
//	slave_deselect(NSS_PIN_POS);

//	/* 3: Set RF Frequency. */
//	slave_select(NSS_PIN_POS);
//	cmd = LLCC68_CMD_SET_RF_FREQUENCY;
//	uint8_t args3[] = {0x39, 0x30, 0x00, 0x00};
//	sendCommand(cmd, args3, sizeof(args3));
//	slave_deselect(NSS_PIN_POS);
//
//	/* 4: Set Buffer base address. */
//	slave_select(NSS_PIN_POS);
//	cmd = LLCC68_CMD_SET_BUFFER_BASE_ADDRESS;
//	uint8_t args4[] = {0x00, 0x80};
//	sendCommand(cmd, args4, sizeof(args4));
//	slave_deselect(NSS_PIN_POS);
//
//	/* 5: Set Modulation params. */
//	slave_select(NSS_PIN_POS);
//	cmd = LLCC68_CMD_SET_MODULATION_PARAMS;
//	uint8_t args5[] = {0x03, 0x41, 0x55, 0x09, 0x0C, 0x00, 0x14, 0x7B};
//	sendCommand(cmd, args5, sizeof(args5));
//	slave_deselect(NSS_PIN_POS);

	/* 6: Set Packet params. */
	slave_select(NSS_PIN_POS);
	cmd = LLCC68_CMD_SET_PACKET_PARAMS;
	uint8_t args6[] = {0x00, 0x20, 0x04, 0x18, 0x00, 0x01, 0xFF, 0x02, 0x01};
	sendCommand(cmd, args6, sizeof(args6));
	slave_deselect(NSS_PIN_POS);

	/* 7: Set DioIrqParams. */
	slave_select(NSS_PIN_POS);
	cmd = LLCC68_CMD_SET_DIO_IRQ_PARAMS;
	uint8_t args7[] = {0x00, 0x02, 0x00, 0x02, 0x00, 0x00, 0x00, 0x00};
	sendCommand(cmd, args7, sizeof(args7));
	slave_deselect(NSS_PIN_POS);

//	/* 8: Set Sync word value. */
//	slave_select(NSS_PIN_POS);
//	cmd = LLCC68_CMD_WRITE_REGISTER;
//	uint8_t args8[] = {0x06, 0xC0, 0x01, 0x02, 0x03};
//	sendCommand(cmd, args8, sizeof(args8));
//	slave_deselect(NSS_PIN_POS);

	/* 9: Set chip to Rx mode. */
	slave_select(NSS_PIN_POS);
	cmd = LLCC68_CMD_SET_RX;
	uint8_t args9[] = {0x00, 0x00, 0x00};
	sendCommand(cmd, args9, sizeof(args9));
	slave_deselect(NSS_PIN_POS);

	while(!(GPIOB->IDR & (1U << IRQ_PIN_POS))) {
//			printf("Waiting for packets...\r\n");
	}

//	slave_select(NSS_PIN_POS);
//	uint8_t cmd = LLCC68_CMD_GET_IRQ_STATUS;
//	uint8_t irqStatus[2];
//	uint8_t args[] = {0x00};
//	sendCommand(cmd, args,1);
//	spi_receive(irqStatus, 2);
//	slave_deselect(NSS_PIN_POS);
//
//	for(int i = 0; i < 3; ++i) {
//		printf("IRQStatus[%d]: 0x%02X\r\n", i, irqStatus[i]);
//	}

	/* Fetch buffer status. This includes size of packet received. */
	slave_select(NSS_PIN_POS);
	cmd = LLCC68_CMD_GET_RX_BUFFER_STATUS;
	uint8_t status[3];
	sendCommand(cmd, NULL,0);
	spi_receive(status, 3);
	slave_deselect(NSS_PIN_POS);

	slave_select(NSS_PIN_POS);
	cmd = LLCC68_CMD_READ_BUFFER;
	uint8_t args10[] = {status[2], 0x00};
	sendCommand(cmd, args10, sizeof(args10));
	spi_receive(buffer, status[1]);
	slave_deselect(NSS_PIN_POS);

	/* 12: Clear IRQ RxDone flag. */
	slave_select(NSS_PIN_POS);
	cmd = LLCC68_CMD_CLEAR_IRQ_STATUS;
	uint8_t args11[] = {0x00, 0x02};
	sendCommand(cmd, args11, sizeof(args11));
	slave_deselect(NSS_PIN_POS);
}

//static configureTxParams(void) {
//
//	uint8_t cmd;
//	/* 1: Set PA config. */
//	slave_select(NSS_PIN_POS);
//	cmd = LLCC68_CMD_SET_PA_CONFIG;
//	uint8_t args4[] = {0x04, 0x07, 0x00, 0x01};
//	sendCommand(cmd, args4, sizeof(args4));
//	slave_deselect(NSS_PIN_POS);
//
//
//	slave_select(NSS_PIN_POS);
//	cmd = LLCC68_CMD_SET_TX_PARAMS;
//	uint8_t args5[] = {0x16, 0x02};
//	sendCommand(cmd, args5, sizeof(args5));
//	slave_deselect(NSS_PIN_POS);
//
//
//	/* 10: Set DioIrqParams. */
//	slave_select(NSS_PIN_POS);
//	cmd = LLCC68_CMD_SET_DIO_IRQ_PARAMS;
//	uint8_t args10[] = {0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00};
//	sendCommand(cmd, args10, sizeof(args10));
//	slave_deselect(NSS_PIN_POS);
//}

void setTx(uint8_t *buffer, uint32_t len) {
	uint8_t cmd;
//
//	/* 1: Set Tx to Stand-by. */
//	slave_select(NSS_PIN_POS);
//	uint8_t cmd = LLCC68_CMD_SET_STANDBY;
//	uint8_t args[] = {0x00};
//	sendCommand(cmd, args, sizeof(args));
//	slave_deselect(NSS_PIN_POS);
//
//	/* 2: Set packet type. */
//	slave_select(NSS_PIN_POS);
//	cmd = LLCC68_CMD_SET_PACKET_TYPE;
//	uint8_t args2[] = {0x00};
//	sendCommand(cmd, args2, sizeof(args2));
//	slave_deselect(NSS_PIN_POS);
//
//	/* 3: Set RF Frequency. */
//	slave_select(NSS_PIN_POS);
//	cmd = LLCC68_CMD_SET_RF_FREQUENCY;
//	uint8_t args3[] = {0x39, 0x30, 0x00, 0x00};
//	sendCommand(cmd, args3, sizeof(args3));
//	slave_deselect(NSS_PIN_POS);


	/* 4: Set PA config. */
	slave_select(NSS_PIN_POS);
	cmd = LLCC68_CMD_SET_PA_CONFIG;
	uint8_t args4[] = {0x04, 0x07, 0x00, 0x01};
	sendCommand(cmd, args4, sizeof(args4));
	slave_deselect(NSS_PIN_POS);


	/* 5: Set Tx params. */
	slave_select(NSS_PIN_POS);
	cmd = LLCC68_CMD_SET_TX_PARAMS;
	uint8_t args5[] = {0x16, 0x02};
	sendCommand(cmd, args5, sizeof(args5));
	slave_deselect(NSS_PIN_POS);

//	/* 6: Set Buffer base address. */
//	slave_select(NSS_PIN_POS);
//	cmd = LLCC68_CMD_SET_BUFFER_BASE_ADDRESS;
//	uint8_t args6[] = {0x00, 0x80};
//	sendCommand(cmd, args6, sizeof(args6));
//	slave_deselect(NSS_PIN_POS);


	/* 7: Write to buffer. */
	slave_select(NSS_PIN_POS);
	cmd = LLCC68_CMD_WRITE_BUFFER;
	uint8_t offset = 0x00U;

	sendCommand(cmd, &offset, 1);
	spi_transmit(buffer, len);
	slave_deselect(NSS_PIN_POS);


//	/* 8: Set Modulation params. */
//	slave_select(NSS_PIN_POS);
//	cmd = LLCC68_CMD_SET_MODULATION_PARAMS;
//	uint8_t args8[] = {0x03, 0x41, 0x55, 0x09, 0x0C, 0x00, 0x14, 0x7B};
//	sendCommand(cmd, args8, sizeof(args8));
//	slave_deselect(NSS_PIN_POS);

	/* 9: Set Packet params. */
	slave_select(NSS_PIN_POS);
	cmd = LLCC68_CMD_SET_PACKET_PARAMS;
	uint8_t args9[] = {0x00, 0x20, 0x04, 0x18, 0x00, 0x01, len, 0x02, 0x01};
	sendCommand(cmd, args9, sizeof(args9));
	slave_deselect(NSS_PIN_POS);


	/* 10: Set DioIrqParams. */
	slave_select(NSS_PIN_POS);
	cmd = LLCC68_CMD_SET_DIO_IRQ_PARAMS;
	uint8_t args10[] = {0x00, 0x01, 0x00, 0x01, 0x00, 0x00, 0x00, 0x00};
	sendCommand(cmd, args10, sizeof(args10));
	slave_deselect(NSS_PIN_POS);

//	/* 11: Set Sync word value. */
//	slave_select(NSS_PIN_POS);
//	cmd = LLCC68_CMD_WRITE_REGISTER;
//	uint8_t args11[] = {0x06, 0xC0, 0x01, 0x02, 0x03};
//	sendCommand(cmd, args11, sizeof(args11));
//	slave_deselect(NSS_PIN_POS);

	/* 12: Set chip to Tx mode. */
	slave_select(NSS_PIN_POS);
	cmd = LLCC68_CMD_SET_TX;
	uint8_t args12[] = {0x00, 0x00, 0x00};
	sendCommand(cmd, args12, sizeof(args12));
	slave_deselect(NSS_PIN_POS);


	/* 13: Wait for the transmission to finish. */
	while(!(GPIOB->IDR & (1U << IRQ_PIN_POS))) { }

	/* 14: Clear IRQ TxDone flag. */
	slave_select(NSS_PIN_POS);
	cmd = LLCC68_CMD_CLEAR_IRQ_STATUS;
	uint8_t args13[] = {0x00, 0x01};
	sendCommand(cmd, args13, sizeof(args13));
	slave_deselect(NSS_PIN_POS);
}

uint8_t getRSSI_Inst(void) {
	uint8_t rssiRaw;
	slave_select(NSS_PIN_POS);
	uint8_t cmd = LLCC68_CMD_GET_RSSI_INST;
	uint8_t args2[] = {0x00};
	sendCommand(cmd, args2, sizeof(args2));
	spi_receive(&rssiRaw, 1);
	slave_deselect(NSS_PIN_POS);

	return rssiRaw;
}


void getPacketStatus(uint8_t *result) {
	slave_select(NSS_PIN_POS);
	uint8_t cmd = LLCC68_CMD_GET_PACKET_STATUS;
	sendCommand(cmd, NULL, 0);
	spi_receive(result, 4);
	slave_deselect(NSS_PIN_POS);
}



