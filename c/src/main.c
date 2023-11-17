#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "lcd.h"
#include "time.h"
#include "buttons.h"

#include "morse_code.h"

void main(void){
    button_tracker_state* button_a = buttons_new_tracker(BUTTON_A);
    button_tracker_state* button_b = buttons_new_tracker(BUTTON_B);
    button_tracker_state* button_c = buttons_new_tracker(BUTTON_C);
    uint8_t translation_len = 0;
    uint8_t translation_end = 0;
    morse_key_t morse_key = morse_key_default();

    //ring buffer for storing the most recent 16 characters. 18 because we
    //need space for 2 null terminators.
    char* translations = calloc(sizeof(char), 18);

    morse_init();
    timer_init();
    lcd_init();

    while(1){
        if(buttons_pressed(button_a)){
            morse_key = morse_append_dah(morse_key);
            lcd_putc('-');
        }
        if(buttons_pressed(button_b)){
            morse_key = morse_append_dit(morse_key);
            lcd_putc('.');
        }
        if(buttons_pressed(button_c) || morse_key_invalid(morse_key)){
            lcd_ddram_addr_set(0x40);
            translations[translation_end] = morse_to_char(morse_key);
            if (translation_len == 16){
                if (translation_end == 16){ //we need to loop back around
                    translation_end = 0;
                }
                else{
                    translation_end++;
                }
                translations[translation_end] = 0;
                lcd_puts(translations + translation_end + 1);
            }
            else {
                translation_len++;
                translation_end++;
            }
            lcd_puts(translations);
            morse_key = morse_key_default();
            lcd_ddram_addr_set(0);
            lcd_puts("       ");// blank out top line
            lcd_ddram_addr_set(0);
        }
    }

    return;
}
