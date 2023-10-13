#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

extern void lcd_init(void);
//extern void lcd_puts(char* s);

void main(void){
    lcd_init();
    // char* uwu = malloc(20);
    // lcd_init();
    // if (!uwu){
    //     lcd_puts("Error!");
    //     return;
    // }

    // memcpy(uwu, "It worked!", 20);

    // lcd_puts(uwu);

    return;
}
