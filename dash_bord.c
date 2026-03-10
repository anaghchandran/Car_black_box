/*
 * File:   
 * Author: <NAME>
 *
 * Created on 1 December, 2023, 10:40 AM
 */


#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "ds1307.h"
#include "i2c.h"

unsigned char time[9];
extern char sp,ev[][3], ev_i;
unsigned char clock_reg[3];
 
void dashboard()
{

    //display logic
   
    clcd_print(" TIME     EV  SP",LINE1(0));
    clcd_print(time,LINE2(0));
    if( sp < 100)
    {
        clcd_putch(sp/10 +48,LINE2(14));
        clcd_putch(sp%10 +48,LINE2(15));
    }
    clcd_print(ev[ev_i],LINE2(10));
    
   
    
    
}
 void get_time(void)
   {
	clock_reg[0] = read_ds1307(HOUR_ADDR);
	clock_reg[1] = read_ds1307(MIN_ADDR);
	clock_reg[2] = read_ds1307(SEC_ADDR);

	if (clock_reg[0] & 0x40)
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x01);    // 12 hrs   
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	else
	{
		time[0] = '0' + ((clock_reg[0] >> 4) & 0x03);    //24 hrs
		time[1] = '0' + (clock_reg[0] & 0x0F);
	}
	time[2] = ':';
	time[3] = '0' + ((clock_reg[1] >> 4) & 0x0F);
	time[4] = '0' + (clock_reg[1] & 0x0F);   //min
	time[5] = ':';
	time[6] = '0' + ((clock_reg[2] >> 4) & 0x0F); //sec
	time[7] = '0' + (clock_reg[2] & 0x0F);
	time[8] = '\0';
  }
 
 void display_time(void)
{
	clcd_print(time, LINE2(2));

	if (clock_reg[0] & 0x40)
	{
		if (clock_reg[0] & 0x20)
		{
			clcd_print("PM", LINE2(12));
		}
		else
		{
			clcd_print("AM", LINE2(12));
		}
	}
}