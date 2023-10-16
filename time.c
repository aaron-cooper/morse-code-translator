#include "time.h"
#include "lcd.h"
#include <stdint.h>

#define ACR_ADDR 0x600b
#define T1CL_ADDR 0x6004
#define T1CH_ADDR 0x6005
#define IER_ADDR 0x600E

extern unsigned long time;

void timer_init(void){
    *(uint8_t*)IER_ADDR = 0b11000000;
    *(uint8_t*)ACR_ADDR = 0b01000000;
    //0x3e6 = 998
    *(uint8_t*)T1CL_ADDR = 0xe6;
    *(uint8_t*)T1CH_ADDR = 0x03;
}

unsigned long timer_get_elapsed_time(void){
    unsigned long time_copy;
    // disable interrupt while copying to prevent funny stuff from happening
    // if this happens to be called at the same time that the timer expires
    __asm__("sei");
    time_copy = time;
    __asm__("cli");
    return time_copy;
}