/*
 * File:   
 * Author: ANAGH CS
 *
 * 
 */



#include <xc.h>
#include "main.h"
#include "eeprom.h"
#include "clcd.h"

char lap, o_f;
extern char time[9];
//char debug[10];
extern char ev[][3], ev_i, sp;

void store_event() {
    //logic for storing 
    char data[10] = {};
    data[0] = time[0];
    data[1] = time[1];
    data[2] = time[3];
    data[3] = time[4];
    data[4] = time[6];
    data[5] = time[7]; // time is soterd.
    /* storing ev*/
    data[6] = ev[ev_i][0];
    data[7] = ev[ev_i][1];
    /*        */
    data[8] = sp / 10 + 48;
    data[9] = sp % 10 + 48;

    for (int i = 0; i < 10; i++) {
        write_internal_eeprom((lap * 10 + i), data[i]);
    }
    lap++;
    if (lap == 10) {
        o_f = 1; //to view the overflow.
        lap = 0;
    }




}