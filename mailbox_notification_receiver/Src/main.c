#include <stdio.h>
#include <string.h>
#include "mail_notification_driver.h"
#include "systick.h"
#include "rtc_driver.h"
#include "rtc_module_driver.h"
#include "ff.h"


#define DEBUG_MODE__
//#define ACTION_DURATION (6U)


/*	Pins used (Receiver device):
 * 	PORT A:
 *
 *
 * */

void checkFRESULT(FRESULT res);
FRESULT makeLog(FIL* file, UINT* bw, uint8_t mail_status);

uint8_t checkHeaderPresent(char* target, char* header, uint32_t headerLen);

int main(void) {
	FATFS fs;   /* File system. */
	FIL file;   /* File handler. */
	FRESULT res; /* Result from file function calls. */
	UINT br; /* Bytes read from file. */
	UINT bw; /* Bytes written to file. */
	uint8_t mail_status = 0;
	uint32_t fileSize; /* Though f_size returns uint64_t, it may be unrealistic
	 	 	 	 	 	  for a CSV file to be that large. So, only the lower 32-bit
	 	 	 	 	 	  will be used for now. */

#ifdef DEBUG_MODE__
	/* For user-LED debug indication. */
	init_debug_mode();
#endif

	/* Mount drive. */
    res = f_mount(&fs, "",0);
	checkFRESULT(res);

	/* Open log file.*/
	res = f_open(&file, "log.csv", FA_WRITE | FA_READ | FA_OPEN_APPEND);
	checkFRESULT(res);

	/* Get lower 32-bit of the returned value of f_size(). */
	fileSize = f_size(&file) & 0xFFFFFFFFU;


	char header[] = "Timestamp: [mm-dd-yyyy] [hh-mm-ss], Status:\r\n";
	uint32_t headerLen = strlen(header);

	/* Contains what is read from file. +1 for null char to be added.
	 * Though, it may not be necessary since memcmp() would use strlen(header)
	 * which returns size not including the null char.*/
	char testRead[headerLen + 1];

	/* Set cursor to beginning. Then perform a read. */
	f_lseek(&file, 0);
	res = f_read(&file, testRead, headerLen, &br);

	checkFRESULT(res);

	if(br != headerLen) {
		debug_led_on();
	}

	/* Add null char to end of the string read from file. */
	testRead[headerLen] = '\0';

	/* Move back the cursor to EOF. To prepare for possible write operations. */
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




	while(1) {
//		receiver_notification(&mail_status);
//
//		if(mail_status == MAIL_PRESENT) {
//		//		debug_led_on();
//			received_led_on();
//			res = makeLog(&file, &bw, mail_status);
//		}
//		else {
//		//		debug_led_off();
//			received_led_off();
//			res = makeLog(&file, &bw, mail_status);
//		}
//
//		res = makeLog(&file, &bw, mail_status);
//
//		res = f_close(&file);

		makeLog(&file, &bw, mail_status);
	}


}

FRESULT makeLog(FIL* file, UINT* bw, uint8_t mail_status) {
	char buff[200];
	getTimeStamp(buff);
	uint8_t lastPos = strlen(buff);

	/* Timestamp + object presence in the mailbox. */
	if(mail_status) {
		sprintf((buff + lastPos), ",OBJECT PLACED IN MAILBOX\r\n");
	}
	else {
		sprintf((buff + lastPos), ",OBJECT TAKEN OUT OF MAILBOX\r\n");
	}

	return(f_write(file, buff, ((UINT)strlen((char*)buff)), bw));
}


/* If at any moment user-led on board lit, there is a problem with file operation. */
void checkFRESULT(FRESULT res) {
	if(res != FR_OK) {
		debug_led_on();
	}
	else {
		debug_led_off();
	}
}





