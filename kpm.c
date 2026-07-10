#include<lpc21xx.h>
#include "kpm_defines.h"
#include "lcd.h"
#include "kpm.h"
#include "typedef.h"
#include "delay.h"
/*u32 kpmLUT[4][4]={{1,2,3,4}, {5,6,7,8}, {9,10,11,12}, {13,14,15,16}};*/
u8 kpmLUT[4][4]={{'7','8','9','/'}, {'4','5','6','*'}, {'1','2','3','-'}, {'c','0','=','+'}};
void InitKPM(void)
{
	IODIR1|=15<<Row1;
}
u32 ColScan(void)
{
	/*if((IOPIN1 & (0xF0 << 20)) != (0xF0 << 20))
        return 0;
    else
        return 1;*/
	return (((IOPIN1>>Col1)&15)<15)?0:1;
}
u32 RowCheck(void)
{
	u32 rno;
	for(rno=0; rno<4; rno++)
	{
	 IOCLR1 = (15 << Row1);        // clear rows
     IOSET1 = ((~(1 <<rno))<<Row1); // make one row low
		if(ColScan()==0)
		{
			break;
		}
}
	//make rows as default
IOPIN1=(IOPIN1&~(15<<Row1))|(0x0<<Row1);
return rno;
}
u32 ColCheck(void)
{
	u32 cno;
for(cno=0;cno<4;cno++)
{
if(((IOPIN1>>(Col1+cno))&1)==0)//we check one by one
{
break;
}
}
return cno;
}
u32 KeyScan(void)
{
	u32 rno,cno,keyv;
	//wait for switch press
	while(ColScan());
	//find the row_no
	rno=RowCheck();
	//find the col_no
	cno=ColCheck();
	//get the key value using kpmLUT
	keyv=kpmLUT[rno][cno];
	//wait for switch release
	while(!ColScan());
	return keyv;
}
u32 Readgap(u8 max)
{
   u8 key;
    u8 digits[5];      // enough for year
    u8 count = 0;
    while(1)
    {
        key = KeyScan();
        if(key >= '0' && key <= '9')
        {
            if(count < max)
            {
                digits[count++] = key;
                lcd_char(key);
            }
        }
        else if(key == 'c')   // Backspace
        {
            if(count > 0)
            {
                count--;
                lcd_cmd(0x10);   // cursor left
                lcd_char(' ');
                lcd_cmd(0x10);
            }
        }
        else if(key == '=')   // Enter
        {
            if(count > 0)
            {
                u32 val = 0;
                u8 i;
                for(i=0;i<count;i++)
                {
                    val = val*10 + (digits[i]-'0');
                }
                return val;
            }
				}
    	}
}
u32 ReadNum(void)
{
	u8 key;
	u32 sum=0;
	while(1)
	{
	key=KeyScan();
		if(key>='0'&&key<='9')
		{
			lcd_char(key);
			sum=(sum*10)+(key-'0');
		}
		else if(key=='=')
		{
			break;
		}
	}
	return sum;
}

