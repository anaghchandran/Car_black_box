
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
#include "eeprom.h"


extern char main_f;
unsigned int attempt = 1;
unsigned int index = 0;
static unsigned char pass[4] = {'0' , '0' , '0', '0'};
static unsigned char input[4] = {0};
int count = 0;
int flag = 0;
char down = 30;
static int intial =0;

void password(char key) {
//    if( intial == 0)
//    {
//        intial = 1;
//        write_internal_eeprom(200, pass[0]); //to avoid garbage value at first ( run only for 1 time)
//        write_internal_eeprom(201, pass[1]);
//        write_internal_eeprom(202, pass[2]);
//        write_internal_eeprom(203, pass[3]);
//    }
    //    
    //    
    //    
    pass[0] = read_internal_eeprom(200); //reading info from eeprom
    pass[1] = read_internal_eeprom(201);
    pass[2] = read_internal_eeprom(202);
    pass[3] = read_internal_eeprom(203);
    //    

    //password logic

    if ((key != ALL_RELEASED) && (index < 4) && (attempt < 4)) {
        //clcd_print(" Enter password ", LINE1(0));
        if (key == 11) {
            input[index] = '0';
        } else if (key == 12) {
            input[index] = '1';

        }

        // ++index;
        clcd_putch('*', LINE2(index));
        index++;
        //for( int j=0;j<30;j++); 
    }

    if (index == 4) {
        for (int y = 0; y < 4; y++) {
            flag = 0;
            if (pass[y] != input[y] && (attempt < 4)) {
                flag = 1;
                attempt++;
                count = count - y;
                index = 0;
                break;
            }
            //flag=1;

        }


        if (attempt == 4) {
            //CLEAR_DISP_SCREEN;

            TMR0ON = 1;
            TMR0IE = 1;
//            index=0;
//            attempt=0;
            if( down ==0)
            {
                TMR0ON = 0;
            TMR0IE = 0;
                down = 120; // Reset the countdown
                attempt = 3; // Reset the attempt counter
                index = 0; // Reset the input index
                flag = 0; // Reset the flag
//                main_f = CHANGEPASS;
                CLEAR_DISP_SCREEN;
            }



        } else if (flag == 1) {
            //CLEAR_DISP_SCREEN;

            for (int y = 0; y < 1000; y++)
                clcd_print("        error   ", LINE2(0));
            index = 0;
            CLEAR_DISP_SCREEN;
            clcd_print(" Enter password ", LINE1(0));

        } else if (flag == 0) {
            //CLEAR_DISP_SCREEN;
            clcd_print("    Success    ", LINE2(0));
            index = 0;
            //for( int o=0;o<50;o++);
            main_f = MENU;
            CLEAR_DISP_SCREEN;
        }

    }

}