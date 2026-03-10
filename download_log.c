/*
 * File:   
 * Author: <NAME>
 *
 * Created on 1 December, 2023, 10:40 AM
 */


#include <xc.h>
#include "main.h"
#include "eeprom.h"
//#include "clcd.h"
#include "uart.h"

unsigned char ch;
extern char main_f;
char debug[10];
static unsigned char index = 0;
void download_log()
{
    //download log logic
    if( index < 10)
    {
     for (int i = 0; i < 10; i++) 
     {
        debug[i] = read_internal_eeprom(((index * 10) + i));
    }
    putch(debug[0]); // hh
    putch(debug[1]);
    putch(':'); // :
    putch(debug[2]); // mm
    putch(debug[3]);
    putch(':'); // :
    putch(debug[4]); // ss
    putch(debug[5]);
    putch(' '); // Space
    putch(' '); // Space
    putch(debug[6]); // Event code (2 bytes)
    putch(debug[7]);
    putch(' '); // Space
    putch(' '); // Space
    putch(debug[8]); // Speed (tens)
    putch(debug[9]); // Speed (units)
     puts("\n\r");
    index++;
    }
    if( index == 10)
    {
        index =0;
        main_f = MENU;
    }
}
