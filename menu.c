/*
 * File:   
 * Author: <NAME>
 *
 * Created on 1 December, 2023, 10:40 AM
 */



#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "matrix_keypad.h"

char prekey = ALL_RELEASED;
extern char main_f;
extern char menu_f;
static char key;

void menu(char key_2) {
    //logic for menu
    char log[][16] = {" view log      ", " download log  ", " clear log   ", " change pass   ", " set time     "};
    static char m_index = 0; //menu index
    static char s_f = 0; //flag
    static unsigned int count1 = 0;
    static unsigned int count2 = 0;
    if (s_f == 0) {
        clcd_putch('*', LINE1(0));
        clcd_putch(' ', LINE2(0));
    } else {
        clcd_putch(' ', LINE1(0));
        clcd_putch('*', LINE2(0));
    }

    clcd_print(log[m_index], LINE1(2));
    clcd_print(log[m_index + 1], LINE2(2));



    key = read_switches(LEVEL_CHANGE);
    

    if (key == MK_SW12) // Key SW12 is pressed
    {
        count1++; // Increment counter for SW12
        if (count1 > 2000) // Long press condition
        {

            // main_f = ;
            CLEAR_DISP_SCREEN;
            main_f = DASHBOARD;

            count1 = 0; // Reset counter after long press
        }
    } else if (count1 > 0 && count1 < 2000) // Short press condition
    {
        count1 = 0;
        if (s_f == 0) // Move between lines
        {
            s_f = 1;
        } else if (m_index < 3) // Navigate through the menu
        {
            m_index++;
        }
    }

    if (key == MK_SW11) // Key SW12 is pressed
    {
        count2++; // Increment counter for SW12
        if (count2 > 2000) // Long press condition
        {
            main_f = MENU_ENTER;
            menu_f = (s_f + m_index);

            count2 = 0; // Reset counter after long press
        }
    } else if (count2 > 0 && count2 < 2000) // Short press condition
    {
        count2 = 0;
        if (s_f == 1) // Move between lines
        {
            s_f = 0;
        } else if (m_index > 0) // Navigate through the menu
        {
            m_index--;
        }
    }
}