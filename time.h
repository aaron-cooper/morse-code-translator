#ifndef TIME_H
#define TIME_H

#include <stdint.h>
#include "lcd.h"


void timer_init(void);
unsigned int timer_get_elapsed_time(void);


#endif