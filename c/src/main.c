#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lcd.h"
#include "time.h"
#include "buttons.h"

char morse_lookup[64];

void init_morse_lookup(void){
    morse_lookup[0b010000] = 'A';
    morse_lookup[0b100011] = 'B';
    morse_lookup[0b101011] = 'C';
    morse_lookup[0b100111] = 'D';
    morse_lookup[0b011111] = 'E';
    morse_lookup[0b001011] = 'F';
    morse_lookup[0b110111] = 'G';
    morse_lookup[0b000011] = 'H';
    morse_lookup[0b001111] = 'I';
    morse_lookup[0b011100] = 'J';
    morse_lookup[0b101000] = 'K';
    morse_lookup[0b010011] = 'L';
    morse_lookup[0b110000] = 'M';
    morse_lookup[0b101111] = 'N';
    morse_lookup[0b111000] = 'O';
    morse_lookup[0b011011] = 'P';
    morse_lookup[0b110100] = 'Q';
    morse_lookup[0b010111] = 'R';
    morse_lookup[0b000111] = 'S';
    morse_lookup[0b100000] = 'T';
    morse_lookup[0b001000] = 'U';
    morse_lookup[0b000100] = 'V';
    morse_lookup[0b011000] = 'W';
    morse_lookup[0b100100] = 'X';
    morse_lookup[0b101100] = 'Y';
    morse_lookup[0b110011] = 'Z';
    morse_lookup[0b011110] = '1';
    morse_lookup[0b001110] = '2';
    morse_lookup[0b000110] = '3';
    morse_lookup[0b000010] = '4';
    morse_lookup[0b000001] = '5';
    morse_lookup[0b100001] = '6';
    morse_lookup[0b110001] = '7';
    morse_lookup[0b111001] = '8';
    morse_lookup[0b111101] = '9';
    morse_lookup[0b111110] = '0';
    morse_lookup[0b111111] = ' ';
}

void main(void){
    button_tracker_state* button_a = buttons_new_tracker(BUTTON_A);
    button_tracker_state* button_b = buttons_new_tracker(BUTTON_B);
    button_tracker_state* button_c = buttons_new_tracker(BUTTON_C);
    uint8_t morse_key = 0;
    uint8_t signals_entered = 0;
    uint8_t chars_entered = 0;

    timer_init();
    init_morse_lookup();
    lcd_init();

    while(1){
        if(buttons_pressed(button_a)){
            signals_entered++;
            morse_key <<= 1;
            morse_key |= 1;
            lcd_putc('-');
        }
        if(buttons_pressed(button_b)){
            signals_entered++;
            morse_key <<=1;
            lcd_putc('.');
        }
        if(buttons_pressed(button_c)){
            char translation = '?'; //? is default if translation can't be found
            uint8_t pad_val; 
            pad_val = morse_key & 1;
            pad_val = !pad_val;
            while(signals_entered < 6){
                morse_key <<= 1;
                morse_key |= pad_val;
                signals_entered++;
            }
            lcd_ddram_addr_set(0x40 + chars_entered);
            if (morse_lookup[morse_key]) translation = morse_lookup[morse_key];
            lcd_putc(morse_lookup[morse_key]);
            lcd_ddram_addr_set(0);
            lcd_puts("       ");// blank out top line
            lcd_ddram_addr_set(0);
            chars_entered++;
            signals_entered = 0;
            morse_key = 0;
        }
    }

    return;
}
