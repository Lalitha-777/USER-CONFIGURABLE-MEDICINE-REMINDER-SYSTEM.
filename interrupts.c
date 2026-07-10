#include <lpc21xx.h>

#include "globals.h"

#include "typedef.h"

#include "interrupts.h"

#include "menusetup.h"

#include "buzzer.h"

#define EINT0_INPUT_PIN 0X0000000C

#define EINT1_INPUT_PIN 0X000000C0

void config_mode(void);

void setup_mode(void);

void eint0_isr(void) __irq

{

    setup_mode();   // Switch-1

	EXTINT = 1<<0;

    VICVectAddr = 0;

}

void eint1_isr(void) __irq

{

    stop_alarm = 0;  // Switch-2

	  buzzer_off();

	 EXTINT = 1<<1;

    VICVectAddr = 0;

}

void interrupt_init(void)

{

    PINSEL0&=~3<<2|~3<<6;

	 PINSEL0|=EINT0_INPUT_PIN|EINT1_INPUT_PIN;

    VICIntEnable = (1<<14) | (1<<15);

	 VICVectCntl0 = (1<<5) | 14;

	 VICVectCntl1 = (1<<5) | 15;

    VICVectAddr0 = (unsigned int) eint0_isr;

    VICVectAddr1 = (unsigned int) eint1_isr;

	EXTMODE=((1<<1)|(1<<0));

}



