#include <stdint.h>
#include "lcd.h"

#define RS 0x1
#define RW 0x2
#define E 0x4

extern void lcd_set_port_b(uint8_t rs, uint8_t rw);
extern void lcd_send(uint8_t data);
extern uint8_t lcd_receive(void);
extern void lcd_set_direction(uint8_t dir);


void lcd_putc(uint8_t port_b, uint8_t port_a){
    
}