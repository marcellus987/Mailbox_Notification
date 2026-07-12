#include <stdio.h>
#include <string.h>
#include "mail_notification_driver.h"
#include "systick.h"
#include "rtc_driver.h"
#include "rtc_module_driver.h"
#include "ff.h"
#include "uart_driver.h"


#define DEBUG_MODE__
//#define ACTION_DURATION (6U)


/*	Pins used (Receiver device):
 * 	PORT A:
 *
 *
 * */


/**** Global variables START. *****/
volatile uint8_t run = 1;

/**** Global variables END. *****/

void checkFRESULT(FRESULT res);
void configureButton(void);
uint8_t checkHeaderPresent(char* target, char* header, uint32_t headerLen);
FRESULT makeLog(FIL* file, UINT* bw, uint8_t mail_status);

int main(void) {
	FATFS fs;   /* File system. */
	FIL file;   /* File handler. */
	FRESULT res; /* Result from file function calls. */
	UINT br; /* Bytes read from file. */
	UINT bw; /* Bytes written to file. */
	uint8_t mail_status = 1;
	uint32_t fileSize; /* Though f_size() returns uint64_t, it may be unrealistic
	 	 	 	 	 	  for a CSV file to be that large. So, only the lower 32-bit
	 	 	 	 	 	  will be used for now. */

	char header[] = "Date: [mm-dd-yyyy], Time (24-hour format): [hh-mm-ss], Status:\r\n";
	uint32_t headerLen = strlen(header);

	char testRead[headerLen + 1]; /* Contains what is read from file. +1 for null char to be added.
	 	 	                       * Though, it may not be necessary since memcmp() would use strlen(header)
	 	 	                       * which returns size not including the null char.*/

#ifdef DEBUG_MODE__
//	uart_init(1);
//	setBaudrate(115200);
	/* For user-LED debug indication. */
	init_debug_mode();
	configureButton();
	received_led_init();
#endif

	rtc_module_init();

	/* Mount drive. */
    res = f_mount(&fs, "",0);
	checkFRESULT(res);

	/* Open log file.*/
	res = f_open(&file, "mail_log.csv", FA_WRITE | FA_READ | FA_OPEN_APPEND);
	checkFRESULT(res);

	/* Get lower 32-bit of the returned value of f_size(). */
	fileSize = f_size(&file) & 0xFFFFFFFFU;

	/* Set cursor to beginning. Then perform a read. */
	f_lseek(&file, 0);
	res = f_read(&file, testRead, headerLen, &br);
	checkFRESULT(res);

//	if(br != headerLen) {
//		debug_led_on();
////		printf("br != headerLen...\r\n");
//	}

	/* Add null char to end of the string read from file. */
	testRead[headerLen] = '\0';

	/* Move back the cursor to EOF. To prepare for possible file write operations. */
	f_lseek(&file, fileSize);

	/* Check if header read from file matches the required header.
	 * Since strlen(header) is used  in memcmp(), it would compare
	 * bytes without the null character because strlen() returns
	 * size not including the null character.
	 *
	 * memcmp returns 0 if each byte from testRead matches those in header.
	 * If not match, there are few cases. But for now, just append the header.
	 * */
	if(memcmp((char*)testRead, header, headerLen) != 0) { /* No match. */
		res = f_write(&file, header, headerLen, &bw);
		checkFRESULT(res);
		if(bw != headerLen) {
			debug_led_on();
		}
	}

	while(run) {
//		receive_notification(&mail_status);

		if(mail_status == MAIL_PRESENT) {
		//		debug_led_on();
			received_led_on();
		}
		else {
		//		debug_led_off();
			received_led_off();
		}

		res = makeLog(&file, &bw, mail_status);
		checkFRESULT(res);

		f_sync(&file);

		delay_ms(2000);
	}

	res = f_close(&file);
	checkFRESULT(res);
	res = f_mount(NULL, "", 0);
	checkFRESULT(res);

	received_led_off();
	debug_led_off();
} /* End of main(). */

FRESULT makeLog(FIL* file, UINT* bw, uint8_t mail_status) {
	char buff[200];
	getTimeStamp(buff);
	uint8_t lastPos = strlen(buff);

	/* Timestamp + object presence in the mailbox. */
	if(mail_status) {
		sprintf((buff + lastPos), ",OBJECT PLACED IN MAILBOX\r\n");
//		printf("Mail present...\r\n");
	}
	else {
		sprintf((buff + lastPos), ",OBJECT TAKEN OUT OF MAILBOX\r\n");
//		printf("No mail...\r\n");
	}


	return(f_write(file, buff, ((UINT)strlen((char*)buff)), bw));
}


/* If at any moment user-led on board lit, there is a problem with file operation. */
void checkFRESULT(FRESULT res) {
	if(res != FR_OK) {
		debug_led_on();
//		printf("res != FR_OK...\r\n");
	}
	else {
		debug_led_off();
//		printf("res == FR_OK...\r\n");
	}
}


/* Configure interrupt for user-button. */
void configureButton(void) {
	/* Disable system interrupt. */
	__disable_irq();

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	/* Input mode.*/
	GPIOA->MODER &= GPIO_MODER_MODER0_Msk;

	/* Enable Pull-up. */
	GPIOA->PUPDR |= GPIO_PUPDR_PUPD0_0;

	/* Configure interrupt for PA0 (User-button) to falling trigger. */
	EXTI->IMR |= EXTI_IMR_MR0;
	EXTI->FTSR |= EXTI_FTSR_TR0;

	/* Set PA0 as source for the interrupt. */
	SYSCFG->EXTICR[0] &= ~SYSCFG_EXTICR1_EXTI0_Msk;

	__NVIC_EnableIRQ(EXTI0_IRQn);

	/* Enable system. */
	__enable_irq();
}

void EXTI0_IRQHandler(void) {
	if(EXTI->PR & EXTI_PR_PR0) {
		EXTI->PR |= EXTI_PR_PR0;
		run = 0;
	}
}




