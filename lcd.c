#include <stdint.h>
#include "lcd.h"

extern void lcd_short_wait(void);
extern void lcd_ir_write(uint8_t instruction);
extern uint8_t lcd_ir_read(void);

void lcd_wait_for_busy_clear(void);
void lcd_wait_for_busy_clear(void){
    while (lcd_busy_flag_read());
}

uint8_t lcd_busy_flag_read(void){
    return (lcd_ir_read() & 0b10000000) > 0;
}

uint8_t lcd_address_counter_read(void){
    return lcd_ir_read() & 0b01111111;
}

void lcd_clear_display(void){
    lcd_wait_for_busy_clear();
    lcd_ir_write(1);
}

void lcd_return_home(void){
    lcd_wait_for_busy_clear();
    lcd_ir_write(0b10);
}

void lcd_set_entry_mode(uint8_t options){
    lcd_wait_for_busy_clear();
    lcd_ir_write(0b100 | options);
}
void lcd_display_control(uint8_t options){
    lcd_wait_for_busy_clear();
    lcd_ir_write(0b1000 | options);
}

void lcd_shift_control(uint8_t options){
    lcd_wait_for_busy_clear();
    lcd_ir_write(0b10000 | options);
}

void lcd_function_set(uint8_t options){
    lcd_wait_for_busy_clear();
    lcd_ir_write(0b100000 | options);
}

void lcd_cgram_addr_set(uint8_t addr){
    lcd_wait_for_busy_clear();
    lcd_ir_write(0b1000000 | addr);
}

void lcd_ddram_addr_set(uint8_t addr){
    lcd_wait_for_busy_clear();
    lcd_ir_write(0b10000000 | addr);
}

void lcd_init(void){
    lcd_function_set(DATA_LENGTH_8_BIT | TWO_LINES | FONT_SIZE_8_DOTS);
    lcd_display_control(DISPLAY_ENABLE | CURSOR_ENABLE | BLINKING_ENABLE);
    lcd_set_entry_mode(CURSOR_RIGHT);
}

void lcd_putc(char c){
    lcd_data_write(c);
}

void lcd_puts(char* str){
    while(*str != 0) {
        lcd_putc(*str);
        str++;
    }
}