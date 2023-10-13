#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "lcd.h"

void main(void){

    int i = 0;
    while(i < 100) i++;
    //temporary until I write driver for w65c22
    __asm__("lda #$ff");
    __asm__("sta %%0110000000000011");
    __asm__("sta %%0110000000000010");
    lcd_init();
    lcd_puts("I'm working OwO");


    return;
}
