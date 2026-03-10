#include <xc.h>
#include "main.h"
#include "clcd.h"
extern char down;
extern unsigned int attempt;
extern unsigned int index;
extern int flag;
extern char main_f;

void __interrupt() isr(void) {
    static unsigned short count = 0;

    if (TMR0IF) {
        TMR0 = TMR0 + 8;

        if (count++ == 20000) {
            //CLEAR_DISP_SCREEN;
            RB0 = !RB0;
            count = 0;
            down--; // Decrease the countdown timer
            //clcd_print("   system locked    ", LINE1(0));
            clcd_print("locked for", LINE2(0));
            clcd_putch((down / 100) + '0', LINE2(11));
            clcd_putch(((down / 10) % 10) + '0', LINE2(12));
            clcd_putch((down % 10) + '0', LINE2(13));
            if (down == 0) {
                down = 120; // Reset the countdown
                attempt = 3; // Reset the attempt counter
                index = 0; // Reset the input index
                flag = 1; // Reset the flag

                TMR0ON = 0; // Stop Timer0
                TMR0IE = 0; // Disable Timer0 interrupts

                CLEAR_DISP_SCREEN;
                clcd_print(" Enter password ", LINE1(0));
//                main_f = PASSWORD;
            }

            //            if (down == 0) 
            //            {
            //                
            //                down = 120;
            //                attempt = 1;
            //                index = 0;
            //                flag =0;
            //                
            //               // clcd_print(" Enter password ", LINE1(0));
            //                TMR0ON = 0;
            //                TMR0IE = 0;
            //                //main_f == PASSWORD;
            //                // menu_f = PASSWORD;
            //
            //            }
        }
        TMR0IF = 0;

    }

}