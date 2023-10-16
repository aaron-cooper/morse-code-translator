#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdint.h>

#define BUTTON_A(x) ((0b00001000 & x) != 0)
#define BUTTON_B(x) ((0b00010000 & x) != 0)
#define BUTTON_C(x) ((0b00100000 & x) != 0)

extern void buttons_preamble(void);
extern uint8_t buttons_get_state(void);

#endif