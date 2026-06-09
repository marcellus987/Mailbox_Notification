#ifndef RTC_DRIVER_H__
#define RTC_DRIVER_H__

#include <stdio.h>
#include <stdint.h>
#include "stm32f4xx.h"

void rtc_init(void);
void setRTC_timer(uint32_t timerDuration);

void disable_wakeup_timer(void);
void clear_rtc_wutf(void);

#endif /* RTC_DRIVER_H__ */
