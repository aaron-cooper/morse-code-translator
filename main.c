#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lcd.h"
#include "time.h"

void main(void){
    char* count_str = (char*)malloc(20);
    uint16_t t = 4000;
    int i = 0;
    lcd_init();
    timer_init();

    while(1){
        if (timer_get_elapsed_time() != t){
            t = timer_get_elapsed_time();
            lcd_ddram_addr_set(0);
            sprintf(count_str, "%d", t);
            lcd_puts(count_str);
        }
    }


    return;
}
