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
#include "ds1307.h"
#include "i2c.h"
extern char main_f;
int count = 0;
static unsigned char sec = 0;
static unsigned char hour = 0;
static unsigned char min = 0;
int mode = 0; //1- enter the chande mode
int blink_flag = 0;
unsigned char key;
extern unsigned char time[9];
int count1 = 0;

void settime(char key) {
    // Read the current key press for mode control
    key = read_switches(LEVEL_CHANGE);

    // Toggle mode when SW10 is pressed
    if (key == 10) {
        mode = !mode;
        if (mode == 0) {
            blink_flag = 0; // Stop blinking in normal mode
        }
    }

    // Increase minutes and hours in setting mode
    if (mode == 1) {
        if (key == 11) { // Increase minutes
            min = (min + 1) % 60;
            blink_flag = 1;
        } else if (key == 12) { // Increase hours
            hour = (hour + 1) % 24;
            blink_flag = 2;
        }
    }

    // Handle time roll-over every 120 seconds
    if (sec == 120) {
        sec = 0;
        min++;
    }
    if (min == 60) {
        min = 0;
        hour++;
    }
    if (hour == 24) {
        hour = 0;
    }

    // Display the current time on the CLCD
    clcd_print("    HH     MM ", LINE1(0));
    clcd_putch(hour / 10 + '0', LINE2(8));
    clcd_putch(hour % 10 + '0', LINE2(9));
    clcd_putch(min / 10 + '0', LINE2(11));
    clcd_putch(min % 10 + '0', LINE2(12));
    clcd_putch(sec / 10 + '0', LINE2(14));
    clcd_putch(sec % 10 + '0', LINE2(15));

    // Handle long press on SW12 to save time to RTC
    if (key == 12) {
        count1++;
        if (count1 > 1000) { // Long press condition
            // Convert to BCD format
            hour = (hour / 10 << 4) | (hour % 10);
            min = (min / 10 << 4) | (min % 10);
            sec = (sec / 10 << 4) | (sec % 10);

            // Write to RTC
            write_ds1307(HOUR_ADDR, hour);
            write_ds1307(MIN_ADDR, min);
            write_ds1307(SEC_ADDR, sec);

            // Reset display and go to dashboard
            CLEAR_DISP_SCREEN;
            main_f = DASHBOARD;

            count1 = 0; // Reset counter
        }
    } else if (count1 > 0 && count1 < 2000) { // Short press reset
        count1 = 0;
    }
}
