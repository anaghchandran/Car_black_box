/*
 * File:   
 * Author: <NAME>
 *
 * Created on 1 December, 2023, 10:40 AM
 */


#include <xc.h>
#include "main.h"
#include "matrix_keypad.h"
#include "clcd.h"
#include"eeprom.h"
extern char main_f, o_f, lap;
extern char menu_f;
char debug[10];
char key;
char key1;
static int count=0, count1=0;
static unsigned char index = 1;

void view_log(char key) {
    for (int i = 0; i < 10; i++) {
        debug[i] = read_internal_eeprom(((index * 10) + i));
    }
    key1 = read_switches(LEVEL_CHANGE);
    if (key1 == MK_SW12) // Key SW12 is pressed
    {
        count1++; // Increment counter for SW12
        if (count1 > 1500) // Long press condition
        {

            // main_f = ;
            CLEAR_DISP_SCREEN;
            main_f = MENU;

            count1 = 0; // Reset counter after long press
        }
    } else if (count1 > 0 && count1 < 2000) // Short press condition
    {
        count1 = 0;
        if (index < 9)
            index++;
    }

//    if (key1 == MK_SW11) // Key SW12 is pressed
//    {
//        count1++; // Increment counter for SW12
//        if (count1 > 2000) // Long press condition
//        {
//
//            //            // main_f = ;
//            CLEAR_DISP_SCREEN;
//            main_f = DASHBOARD;
//
//            count1 = 0; // Reset counter after long press
//        }
//    }
    
    
    
    
    //    else if (count1 > 0 && count1 < 2000) // Short press condition
    //    {
    //        count1 = 0;
    //        if( index > 0)
    //        index--;
    //    }



    clcd_putch(debug[0], LINE2(0)); // hh
    clcd_putch(debug[1], LINE2(1));
    clcd_putch(':', LINE2(2)); // :
    clcd_putch(debug[2], LINE2(3)); // mm
    clcd_putch(debug[3], LINE2(4));
    clcd_putch(':', LINE2(5)); // :
    clcd_putch(debug[4], LINE2(6)); // ss
    clcd_putch(debug[5], LINE2(7));
    clcd_putch(' ', LINE2(8)); // Space
    clcd_putch(' ', LINE2(9)); // Space
    clcd_putch(debug[6], LINE2(10)); // Event code (2 bytes)
    clcd_putch(debug[7], LINE2(11));
    clcd_putch(' ', LINE2(12)); // Space
    clcd_putch(' ', LINE2(13)); // Space
    clcd_putch(debug[8], LINE2(14)); // Speed (tens)
    clcd_putch(debug[9], LINE2(15)); // Speed (units)


}
