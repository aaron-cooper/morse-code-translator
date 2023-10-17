#ifndef BUTTONS_H
#define BUTTONS_H

#include <stdint.h>
#include <stdbool.h>

#define BUTTON_A 0b00001000
#define BUTTON_B 0b00010000
#define BUTTON_C 0b00100000

typedef struct {
    unsigned long cooldown;
    bool pressed;
    uint8_t button;
} button_tracker_state;

extern void buttons_preamble(void);

button_tracker_state* buttons_new_tracker(uint8_t button);
void buttons_free_tracker(button_tracker_state* tracker);
bool buttons_pressed(button_tracker_state* tracker);

#endif