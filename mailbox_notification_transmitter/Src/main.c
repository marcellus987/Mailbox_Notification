#include <stdio.h>
#include "mail_notification_driver.h"
#include "systick.h"
#include "rtc_driver.h"

#define DEBUG_MODE__
#define ACTION_DURATION (6U)
void configureButton(void);

volatile uint8_t mail_status = 0x00;

int main(void) {
//	configureButton();
//	init_debug_mode();
//	while(1) {
//
//	}
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
			delay_ms(1000);
			debug_led_off();
			delay_ms(1000);
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
//	/* For debug. */
//	for(volatile int i = 0; i < 2; ++i) {
		debug_led_on();
		delay_ms(2000);
//	}
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


/* Configure interrupt for user-button. */
void configureButton(void) {
	/* Disable system interrupt. */
	__disable_irq();

	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	RCC->APB2ENR |= RCC_APB2ENR_SYSCFGEN;

	/* Input mode.*/
	GPIOA->MODER &= ~GPIO_MODER_MODER0_Msk;

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
		mail_status ^= mail_status;
		toggle_led();
		send_notification(mail_status);
	}
}
