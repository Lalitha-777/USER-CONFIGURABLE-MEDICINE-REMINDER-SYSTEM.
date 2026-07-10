#include<lpc21xx.h>

#include "typedef.h"

#include "delay.h"

#include "lcd.h"

#include "lcd_defines.h"

void lcd_cmd(u8 cmd)

{

IOCLR0=1<<RS;

IOCLR0=1<<RW;

IOPIN0=(IOPIN0&~(0XFF<<8))|(cmd<<8);//WORD=(WORD&~(0xff<<SBITPOS))|(BYTE<<SBITPOS)

IOSET0=1<<EN;

delay_us(1);

IOCLR0=1<<EN;

delay_ms(2);

}

void lcd_data(u8 data)

{

IOSET0=1<<RS;

IOCLR0=1<<RW;

	IOPIN0=(IOPIN0&~(0XFF<<8))|(data<<8);

IOSET0=1<<EN;

delay_us(1);

IOCLR0=1<<EN;

delay_ms(2);

}
void lcd_init(void)
{
IODIR0|=7<<16;
IODIR0|=0XFF<<8;
delay_ms(15);
lcd_cmd(0x30);
delay_ms(5);
lcd_cmd(0x30);

delay_us(100);

lcd_cmd(0x30);

lcd_cmd(0x38);

lcd_cmd(0x0E);

lcd_cmd(0x01);

lcd_cmd(0x06);

}

void lcd_char(s8 ch)

{

lcd_data(ch);

}

void lcd_str(s8 *str)

{

while(*str)

{

lcd_data(*str);

str++;

}

}

void lcd_int(s32 num)

{

 s32 i=0;

 u8 arr[10];

 if(num<0)

 {

        lcd_data('-');

 }

 else

 {

         while(num)

         {

                arr[i++]=(num%10)+48;

                 num/=10;

         }

 }

 for(--i;i>=0;i--)

 {

        lcd_data(arr[i]);

 }

}

void lcd_float(f32 num,u8 ndp)

{

int n;

s32 i;

        if(num <0)

        {

                lcd_char('-');

        }

        else

        {

                n=num;

                lcd_int(n);

                lcd_char('.');

                for(i=0;i<ndp;i++)

                {

                        num=(num-n)*10;

                        n=num;

                        lcd_char(n+48);

                }

        }

}

/*void lcd_buildCGRAM(u8 *p,u8 nb)

{

s32 i;

lcd_cmd(0X40);

for(i=0;i<=8;i++)

{

lcd_char(CGRAMLUT[i]);

}

lcd_cmd(GOTO_LINE1_POS0);

lcd_data(0x00);

}*/



