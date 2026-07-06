#include <stdio.h>
#include "mail_notification_driver.h"
#include "systick.h"
#include "rtc_driver.h"
#include "sd_card_driver.h"
#include "LLCC68_driver.h"
#include "ff.h"

#define DEBUG_MODE__
//#define ACTION_DURATION (6U)


/*	Pins used (Receiver device):
 * 	PORT A:
 *
 *
 * */

int main(void) {
	FATFS fs;
	FIL file;
	uint8_t mail_status = MAIL_ABSENT;

	FRESULT res = f_mount(&fs, "",0);

	init_debug_mode();

	/* Mount drive. */
	if(res != FR_OK) {
//	    printf("Error mounting drive.\r\n");
		debug_led_on();
	}
	else {
//		printf("Successfully mounted drive.\r\n");
	}

	/* Open log file.*/
	res = f_open(&file, "log.csv", FA_WRITE | FA_READ | FA_OPEN_APPEND);

	if(res != FR_OK) {
//		printf("Error opening file: %d\r\n", res);
		debug_led_on();
	}
	else {
//	   printf("Successfully opened file: %d\r\n", res);
	}


	received_led_init(); /* Initialize LED indicators. */

//	LLCC68_init(); /* Initialize RF-Receiver module. */
//	setRx(&mail_status); /* Set on receive-mode. */

	char header[50] = "Date:, Time:, Status:\r\n";
	char msg1[100] = "01/01/2000, 01:01:01, MAIL RECEIVED\r\n"; /* Log message to write. */
	char msg2[100] = "01/01/2000, 01:01:01, MAIL EMPTIED\r\n"; /* Log message to write. */
	UINT bw; /* Contains the bytes written to file. */

	res = f_write(&file, header, strlen(header), &bw);

	if(mail_status == MAIL_PRESENT) {
//		debug_led_on();
		received_led_on();
		res = f_write(&file, msg1, strlen(msg1), &bw);
	}
	else {
//		debug_led_off();
		received_led_off();
		res = f_write(&file, msg2, strlen(msg2), &bw);
	}

	res = f_close(&file);
}
