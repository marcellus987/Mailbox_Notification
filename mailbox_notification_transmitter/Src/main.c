#include <stdio.h>
#include "mail_notification_driver.h"
#include "systick.h"
#include "rtc_driver.h"

#define DEBUG_MODE__
#define ACTION_DURATION (6U)


int main(void) {
	uint8_t wakeFromStandby = check_standby_flag();
	init_debug_mode();

	/* Awaken from standy-by mode. */
	if(wakeFromStandby) {
		uint8_t isMailPresent;

		/* Initial check to be compared after deep sleep. */
		uint8_t init_mail_status = verify_mail_presence();
		reset_low_power_mode_flags();

#ifdef DEBUG_MODE__
		/* For debug. */
		for(volatile int i = 0; i < 2; ++i) {
			debug_led_on();
			delay_ms(500);
			debug_led_off();
			delay_ms(500);
		}
#endif
		/* Go to deep sleep for 1 minute. Mail is either being placed inside or taken out of the mailbox. */
		wait_for_action_done(ACTION_DURATION);
		isMailPresent = verify_mail_presence();

		/* Cases:
		 * Case #1: If isMailPresent = 1 && init_mail_status = 0, then mail just got in the mailbox.
		 * Case #2: If isMailPresent = 0 && init_mail_status = 1, then mail was taken out of the mailbox.
		 * Case #3: If isMailPresent = 0 && init_mail_status = 0, then false alarm. No notification will be sent.
		 * */
		if(isMailPresent) { /* Case #1. */
			debug_led_on();
			send_notification(MAIL_PRESENT);
		}
		else { /* else, either false alarm or mail is taken out of the mailbox. */

#ifdef DEBUG_MODE__
			/* For debug. */
			for(volatile int i = 0; i < 3; ++i) {
				debug_led_on();
				delay_ms(100);
				debug_led_off();
				delay_ms(100);
			}
#endif
			if(init_mail_status == 1) { /* Case #2. */
				send_notification(MAIL_ABSENT);
			}
			/* else, Case #3 just go to standby mode. */
		}
	}

#ifdef DEBUG_MODE__
	/* For debug. */
	for(volatile int i = 0; i < 2; ++i) {
		debug_led_on();
		delay_ms(2000);
	}
#endif

	/* Go to stand-by mode and wait for mailbox lid to trigger wake-up. */
	set_standby_mode();
} /* End of main(). */


void RTC_WKUP_IRQHandler(void) {
	if(EXTI->PR & EXTI_PR_PR22) {
		EXTI->PR |= EXTI_PR_PR22;
		reset_low_power_mode_flags();
		disable_wakeup_timer();
	}
} /* End of RTC_WKUP_IRQHandler(). */



