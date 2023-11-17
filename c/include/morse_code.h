#ifndef MORSE_CODE_H
#define MORSE_CODE_H

#include <stdint.h>

// the type used to store a sequence of dits and dahs, used to lookup
// associated chars
#define morse_key_t uint8_t

// represents an "empty" morse_key_t with no dits or dahs.
// This must be used to initialize morse_key_t's for morse
// functions to work properly
#define morse_key_default() ((morse_key_t)0b1)

// must call before calling any other morse functions (not including
// morse_key_default)
void morse_init(void);

// maps a morse_key_t to its associated char. If no associated char
// exists, '?' is returned.
char morse_to_char(morse_key_t);

// given a morse_key_t, returns a new morse_key_t with a dit appended
// to the end.
morse_key_t morse_append_dit(morse_key_t);

// given a morse_key_t, returns a new morse_key_t with a dah appended
// to the end.
morse_key_t morse_append_dah(morse_key_t);

// given a morse_key_t, returns true if the given key does map to a
// character, and the key could not be made to map to a character
// by appending additional dits or dahs. Note that this function
// can return false for a morse_key_t that is currently invalid,
// but will never return true for a morse_key_t that is currently valid.
#define morse_key_invalid(morse_key) (morse_key & 0b1000000)
// if bit 6 (starting from 0) is set, one of the morse_append functions
// has been called too many times, and morse_key is invalid


#endif