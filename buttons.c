#include <stdlib.h>
#include "buttons.h"
#include "time.h"

#define BUTTON_COOLDOWN 50

extern uint8_t buttons_get_state_raw(void);

button_tracker_state* buttons_new_tracker(uint8_t button){
    button_tracker_state* new_state = malloc(sizeof(button_tracker_state));
    new_state->cooldown = 0;
    new_state->pressed = false;
    new_state->button = button;
    return new_state;
}

void buttons_free_state(button_tracker_state* tracker){
    free(tracker);
}

bool buttons_pressed(button_tracker_state* tracker){
    unsigned long curr_time = timer_get_elapsed_time();
    uint8_t button = ((tracker->button) & buttons_get_state_raw()) > 0;
    if (button){
        if (!(tracker->pressed)){
            tracker->cooldown = curr_time + BUTTON_COOLDOWN;
            tracker->pressed = true;
            return true;
        }
    }
    else if(tracker->cooldown < curr_time){
        tracker->pressed = false;
    }
    return false;
}

