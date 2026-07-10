#include <lpc21xx.h>

#include "lcd.h"

#include "delay.h"

#include "kpm.h"

#include "rtc.h"

#include "buzzer.h"

#include "globals.h"

#include "menusetup.h"

void setup_mode(void)

{

    int h=0,m=0,s=0,d=1,mo=1,y=2026;

    char key;

	 while(1)

	 {

		lcd_cmd(0x01);

	  lcd_cmd(GOTO_LINE1_POS0);

	  lcd_str("1:RTC 2:MED");

		lcd_cmd(0XC0);

		lcd_str("3:EXIT");

    // wait for valid key

   while(1)

    {

        key = KeyScan();

        if(key == '1'|| key == '2' || key=='3');

		{

            break;

		}

	}

    if(key == '1')
	{
	  	while(1)

		  {

			  lcd_cmd(0x01);

        lcd_cmd(0x80);

			  lcd_str("1.Hr 2.Min 3.Sec");

			  lcd_cmd(0XC0);

			  lcd_str("4.Dat 5.Mo 6.Ye 7.exit");

			  key=KeyScan();

        switch(key)

		    {

			   case '1':

				          h = validvalue("HH:",23);

			            break;

			   case '2':

					        m = validvalue("MM:",59);

			           break;

			   case '3':

					       s = validvalue("SS:",59);

				         break;

			   case '4':

					       d= validvalue("Day:",31);

				         break;

		     case '5':

					      mo = validvalue("Month:",12);

				        break;

				 case '6':

				        y= validvalue("year:",5000);

				        break;

			   case '7':

			          RTC_SetTime(h,m,s);

			          RTC_SetDate(d,mo,y);

				        //return;

				 goto MENU;

			 }

		 }

	 }

    else if(key == '2')

    {

      for(med_count=0;med_count<MAX_MED;med_count++)

      {

            while(1)
            { 
             lcd_cmd(0x01);
	          lcd_cmd(0x80);
	          lcd_str("1.med_hr 2.med_min");
	           lcd_cmd(0xC0);
	           lcd_str("3.exit");
	           key=KeyScan();
	           switch(key)
           	 {
	           case '1': med_hr[MAX_MED]=validvalue("HH:",23);
	                     break;
	           case '2': med_min[MAX_MED]=validvalue("MM:",59);
	                     break;
	           /*case '3': s=validvalue("SS:",59);
	                     break;	*/
	           case '3': 
	                     goto MENU;
	         }	
          }

        }

    }

		else if(key=='3')

		{

			lcd_cmd(0x01);

			lcd_str("EXITING....");

			delay_ms(500);

			lcd_cmd(0x01);

			return;

		}

		MENU: ;

	}

}

u32 validvalue(s8 *msg, u32 max)

{

	u32 val;

    while(1)

    {

        lcd_cmd(0x01);

			  lcd_cmd(0x80);

        lcd_str(msg);		

			if(max == 23)

            lcd_str("00-23");

        else if(max == 59)

            lcd_str("00-59");

        else if(max == 31)

            lcd_str("01-31");

        else if(max == 12)

            lcd_str("01-12");

        else if(max == 6)

            lcd_str("0-6");

			      lcd_cmd(0xC0);

			if(max > 100)

			{

            val = Readgap(4);  

			}				

      else

			{

            val = Readgap(2);

			 }				 

       if(val <= max)

            return val;

       lcd_cmd(0x01);

       lcd_str("INVALID");

       delay_ms(1000);

    }

}

void check_medicine(void)

{

    int h,m,s;

    int i;

    int timer;

    RTC_ReadTime(&h,&m,&s);

    for(i=0;i<med_count;i++)

    {

        if(h==med_hr[i] && m==med_min[i] && s==0)

        {

            stop_alarm = 1;

            timer = 0;

            lcd_cmd(0x01);

            lcd_str("Take Medicine");

            while(stop_alarm && timer < 60)

            {
			 lcd_str("Take Medicine");

                buzzer_on();

                delay_ms(500);

                buzzer_off();

                delay_ms(500);

                timer++;

            }

            buzzer_off();

            stop_alarm = 0;

        }

    }

}



