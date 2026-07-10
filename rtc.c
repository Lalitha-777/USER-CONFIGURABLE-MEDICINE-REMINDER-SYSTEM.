#include <lpc21xx.h>

#include "lcd.h"

#include "lcd_defines.h"

#include "typedef.h"

#include "delay.h"

#include "rtc.h"

// System Clock

#define FOSC 12000000

#define CCLK (5*FOSC)

#define PCLK (CCLK/4)

// Prescaler values

#define PREINT_VAL ((PCLK/32768)-1)

#define PREFRAC_VAL (PCLK-((PREINT_VAL+1)*32768))

#define RTC_ENABLE (1<<0)

#define RTC_RESET  (1<<1)

#define RTC_CLKSRC (1<<4)

// Global variables

int hour,min,sec,date,month,year;

// RTC INITIALIZATION 

void RTC_Init()

{

    CCR = RTC_RESET;        // Reset RTC counters

    PREINT  = PREINT_VAL;   // Integer part

    PREFRAC = PREFRAC_VAL;  // Fraction part

   // CCR = RTC_ENABLE;       // Enable RTC

	CCR = RTC_ENABLE | RTC_CLKSRC;  // FIXED

}

// SET INITIAL TIME

void RTC_SetTime(int h,int m,int s)

{

    HOUR = h;

    MIN  = m;

    SEC  = s;

}

// SET DATE 

void RTC_SetDate(int d,int mo,int y)

{

    DOM   = d;

    MONTH = mo;

    YEAR  = y;

}

// READ TIME 

void RTC_ReadTime(int *h,int *m,int *s)

{

    *h = HOUR;

    *m = MIN;

    *s = SEC;

}

// READ DATE

void RTC_ReadDate(int *d,int *mo,int *y)

{

    *d  = DOM;

    *mo = MONTH;

    *y  = YEAR;

}

// DISPLAY TIME ON LCD

void RTC_DisplayTime(int h,int m,int s)

{

	

    lcd_cmd(GOTO_LINE1_POS0);

    lcd_char((h/10)+48);

    lcd_char((h%10)+48);

    lcd_char(':');

    lcd_char((m/10)+48);

    lcd_char((m%10)+48);

    lcd_char(':');

    lcd_char((s/10)+48);

    lcd_char((s%10)+48);

}

// DISPLAY DATE ON LCD

void RTC_DisplayDate(int d,int mo,int y)

{

    lcd_cmd(GOTO_LINE2_POS0);

    lcd_char((d/10)+48);

    lcd_char((d%10)+48);

    lcd_char('/');

    lcd_char((mo/10)+48);

    lcd_char((mo%10)+48);

    lcd_char('/');

    lcd_int(y);

}

