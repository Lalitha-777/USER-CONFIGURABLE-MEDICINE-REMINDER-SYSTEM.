#include <lpc21xx.h>

#include "typedef.h"

#include "delay.h"

#include "buzzer.h"

void buzzer_init(void)

{

    IODIR0 |= (1<<7);

}

void buzzer_on(void)

{

    IOSET0 = (1<<7);

}

void buzzer_off(void)

{

    IOCLR0 = (1<<7);

}

