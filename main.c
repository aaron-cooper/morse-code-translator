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
    uint8_t button;
    bool pressed = false;
    int presses = 0;
    unsigned long cooldown_end;
    unsigned long curr_time = 0;

    buttons_preamble();
    lcd_init();
    timer_init();


    while(1){
        button = BUTTON_A(buttons_get_state());
        curr_time = timer_get_elapsed_time();
        if (button){
            if (!pressed){
                cooldown_end = curr_time + 3000;
                pressed = true;
                presses++;
                sprintf(buttons_str, "%d", presses);
                lcd_ddram_addr_set(0);
                lcd_puts(buttons_str);
            }
        }
        else if(cooldown_end < curr_time){
            pressed = false;
        }
    }


    return;
}
