#include <lpc21xx.h>
#include "lcd.h"
#include "rtc.h"
#include "kpm.h"
#include "delay.h"
#include "buzzer.h"
#include "interrupts.h"
#include "menusetup.h"
#include "globals.h"
int med_hr[MAX_MED];
int med_min[MAX_MED];
int med_count = 0;
volatile int stop_alarm = 0;
int main()
{
    int h,m,s,d,mo,y;
    interrupt_init();
    RTC_Init();
    lcd_init();
    InitKPM();
    buzzer_init();
    RTC_SetTime(16,15,0);
    RTC_SetDate(20,3,2026);
    while(1)
    {
	 if(stop_alarm==0)
	 {
        RTC_ReadTime(&h,&m,&s);

        RTC_ReadDate(&d,&mo,&y);

        RTC_DisplayTime(h,m,s);

        RTC_DisplayDate(d,mo,y);

	 }

        if(med_count > 0)

            check_medicine();

        delay_s(1);

    }

}

