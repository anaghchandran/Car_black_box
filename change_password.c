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
unsigned int index = 0;
//unsigned int index1 = 0;
//extern unsigned char pass[4] = {0};
static unsigned char input[4] = {0};
//static status = 0; // 1 when success
int count = 15;
int flag = 0;
char down = 120;
unsigned int attempt = 1;

void change_pass(char key) {
    //change password logic
   // clcd_print(" Reenter password ", LINE1(0));
//    pass[0] = read_internal_eeprom(200); //reading info from eeprom
//    pass[1] = read_internal_eeprom(201);
//    pass[2] = read_internal_eeprom(202);
//    pass[3] = read_internal_eeprom(203);

//    if ((key != ALL_RELEASED) && (index < 4) && (attempt < 4)) {
//        //clcd_print(" Enter password ", LINE1(0));
//        if (key == 11) {
//            input[index] = '0';
//        } else if (key == 12) {
//            input[index] = '1';
//
//        }
//
//        // ++index;
//        clcd_putch('*', LINE2(index));
//        index++;
//        //for( int j=0;j<30;j++); 
//    }
//
//    if (index == 4) {
//        for (int y = 0; y < 4; y++) {
//            flag = 0;
//            if (pass[y] != input[y] && (attempt < 4)) {
//                flag = 1;
//                attempt++;
//                count = count - y;
//                index = 0;
//                break;
//            }
//            //flag=1;
//
//        }
//
//
//        if (attempt == 4) {
//            //CLEAR_DISP_SCREEN;
//
//            TMR0ON = 1;
//            TMR0IE = 1;
//
//
//
//        } else if (flag == 1) {
//            //CLEAR_DISP_SCREEN;
//
//            for (int y = 0; y < 1000; y++)
//                clcd_print("        error   ", LINE2(0));
//            index = 0;
//            CLEAR_DISP_SCREEN;
//           // clcd_print(" new password ", LINE1(0));
//
//        } else if (flag == 0) {
//            //CLEAR_DISP_SCREEN;
//            clcd_print("    Success    ", LINE2(0));
//            index = 0;
//            status = 1;
//            for( int o=0;o<5000;o++);
//            //main_f = MENU;
//            CLEAR_DISP_SCREEN;
//        }
//
//    }







    if ((key != ALL_RELEASED) && (index < 4)) {
        
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
        write_internal_eeprom(200, input[0]); //to avoid garbage value at first ( run only for 1 time)
        write_internal_eeprom(201, input[1]);
        write_internal_eeprom(202, input[2]);
        write_internal_eeprom(203, input[3]);
        index = 0;
        for (int y = 0; y < 1000; y++)
            clcd_print(" changed    ", LINE2(0));
       // status = 0;
        main_f = DASHBOARD;
    }
}