/*
 * File:   
 * Author: <NAME>
 *
 * Created on 1 December, 2023, 10:40 AM
 */



#include <xc.h>
#include "main.h"
#include "clcd.h"
#include "eeprom.h"

static int i = 0;
char lap, o_f;
extern char main_f;

void clear_log(char key) {
    //logic for clear
    char data[10] = {};
    for (int i = 0; i < 10; i++) {
        write_internal_eeprom((lap * 10 + i), data[i]);
    }

    CLEAR_DISP_SCREEN;
    for (int y = 0; y < 1000; y++)
        clcd_print(" log are cleared ", LINE2(0));
    main_f = DASHBOARD;


}