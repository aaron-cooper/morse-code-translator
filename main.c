#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lcd.h"
#include "time.h"
#include "buttons.h"

void main(void){
    char* buttons_str = (char*)malloc(20);
    button_tracker_state* button_state = buttons_new_tracker();
    int presses = 0;

    buttons_preamble();
    lcd_init();
    timer_init();

    lcd_puts("hello");


    while(1){
        if(buttons_pressed(button_state, BUTTON_A)){
            presses++;
            sprintf(buttons_str, "%d", presses);
            lcd_ddram_addr_set(0);
            lcd_puts(buttons_str);
        }
    }


    return;
}
