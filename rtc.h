#include<lpc21xx.h>

#include "delay.h"

#include "typedef.h"

void RTC_Init(void);


void RTC_SetTime(int h,int m,int s);

void RTC_SetDate(int d,int mo,int y);


void RTC_ReadTime(int *h,int *m,int *s);

void RTC_ReadDate(int *d,int *mo,int *y);


void RTC_DisplayTime(int h,int m,int s);

void RTC_DisplayDate(int d,int mo,int y);

