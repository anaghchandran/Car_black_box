/*
 * File:   
 * Author: <NAME>
 *
 * Created on 1 December, 2023, 10:40 AM
 */


#include <xc.h>
#include "main.h"
#include "adc.h"
#include "clcd.h"
#include "eeprom.h"
#include "matrix_keypad.h"
#include "timer0.h"
#include "isr.h"
#include "ds1307.h"
#include "i2c.h"
#include "uart.h"

char main_f = 0, menu_f = 0, key, sp;
char ev[][3] = {"ON", "GR", "GN", "G1", "G2", "G3", "G4", " C", "DL", "CL", "ST", "CP"};
char ev_i;

void init_config() {
    //
    PEIE = 1;
    GIE = 1;
    init_clcd();
    init_adc();
    init_matrix_keypad();
    init_timer0();



    //init_clcd();
    init_i2c();
    init_ds1307();
    init_uart();
}

void main(void) {
    init_config();
    store_event();

    while (1) {
        /*
         * get the time 
         * 
         * based on switch press change the event
         */
        get_time();
        sp = read_adc(CHANNEL4) / 10.33;

        key = read_switches(STATE_CHANGE);

        if (key == MK_SW2) {
            if (ev_i < 6)
                ev_i++;
            else if (ev_i == 7)
                ev_i = 2;
            store_event();
        } else if (key == MK_SW3) {
            if (ev_i == 7)
                ev_i = 2;
            else if (ev_i > 1)
                ev_i--;
            store_event();
        } else if (key == MK_SW1) {
            ev_i = 7;
            store_event();
        }
        if (main_f == DASHBOARD) {
            dashboard();
            if (key == MK_SW11) {
                CLEAR_DISP_SCREEN;
                main_f = PASSWORD;
                clcd_print(" Enter password ", LINE1(0));


            }


        } else if (main_f == PASSWORD) {
            
            password(key);
        } else if (main_f == MENU) {
            menu(key);
        } else if (main_f == MENU_ENTER) {
            CLEAR_DISP_SCREEN;
            clcd_print(" View menu ", LINE1(0));
            if (menu_f == VIEWLOG) {
                view_log(key);
            } else if (menu_f == DOWNLOADLOG) {
                CLEAR_DISP_SCREEN;
//                TMR0ON = 1;
//                TMR0IE = 1;
                clcd_print(" Download log ", LINE1(0));
                download_log();
            } else if (menu_f == CLEARLOG) {
                CLEAR_DISP_SCREEN;
                clcd_print(" Clear log  ", LINE1(0));
                clear_log(key);
            } else if (menu_f == SETTIME) {
                CLEAR_DISP_SCREEN;
                clcd_print(" set time   ", LINE1(0));
                settime(key);
            } else if (menu_f == CHANGEPASS) {
                CLEAR_DISP_SCREEN;
                clcd_print(" Enter new pass ", LINE1(0));
                change_pass(key);
            }
        }

    }
    return;
}
