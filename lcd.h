#ifndef LCD_H
#define LCD_H

extern uint8_t lcd_data_read(void);
extern void lcd_data_write(uint8_t data);

uint8_t lcd_busy_flag_read(void);
uint8_t lcd_address_counter_read(void);
void lcd_clear_display(void);
void lcd_return_home(void);


#define CURSOR_LEFT 0
#define CURSOR_RIGHT 0b10
#define DISPLAY_SHIFT 0b1
void lcd_set_entry_mode(uint8_t options);

#define DISPLAY_ENABLE 0b100
#define CURSOR_ENABLE 0b10
#define BLINKING_ENABLE 0b1
void lcd_display_control(uint8_t options);

#define DISPLAY_MOVE 0b1000
#define CURSOR_MOVE 0
#define MOVE_RIGHT 0b100
#define MOVE_LEFT 0
void lcd_shift_control(uint8_t options);

#define DATA_LENGTH_8_BIT 0b10000
#define DATA_LENGTH_4_BIT 0
#define TWO_LINES 0b1000
#define ONE_LINE 0
#define FONT_SIZE_10_DOTS 0b100
#define FONT_SIZE_8_DOTS 0
void lcd_function_set(uint8_t options);

void lcd_cgram_addr_set(uint8_t addr);
void lcd_ddram_addr_set(uint8_t addr);




void lcd_init(void);
void lcd_putc(char c);
void lcd_puts(char* str);

#endif 