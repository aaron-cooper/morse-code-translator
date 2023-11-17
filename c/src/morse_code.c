#include "morse_code.h"


/**
 * Description of morse keys.
 * Morse keys come in 2 forms: unfinalized and finalized.
 * 
 * Unfinalized morse keys begin with 2-7 zeroes, followed a 1, followed by 0-5
 * DIT's (0) and DAH's (1). The left most 1 is used to signify the beginning of
 * the data. If the morse_append functions have been called too many
 * times, then the 1 will be found in bit 6 (LSB is bit 0).
 * Examples:
 *  'A' = .- = 0b00000101
 *  'X' = -..- = 0b00011001
 *
 * Finalized morse keys are 6 bits. The most significant bits contain the DIT's
 * and DAH's. The rest of the bits are padded with the value opposite the final
 * DIT or DAH. This is to remove ambiguity. Consider the value 0b00000001.
 * Assuming 0's are dits, and 1's are dahs, this value could represent both 
 * 'T' (- = 1) or 'U' (..- = 001), since it's impossible to tell whether the 0's
 * are part of the key or not. This ambiguity can be solved by ensuring that the
 * leftmost dit/dah is in bit 4. This results in another ambiguity. Now 0b10000
 * could be 'T', or it could be '6', since it's impossible to tell whether the
 * 0's are part of the key. We can solve this by shifting the start of the key
 * 1 more bit, and ending the key with a series of 0's if the key ends with a
 * dah, or a series of 1's if the key ends with a dit.
 * Examples:
 * 'A' = .- = 0b010000
 * 'X' = -..- = 0b100100
*/


// transform morse_key_t to a value that can be used to find
// and associated character in morse_lookup.
morse_key_t morse_finalize(morse_key_t);

#define DIT ((morse_key_t)0)
#define DAH ((morse_key_t)1)

char morse_lookup[0x64];

void morse_init(void){
    // it looks like the compiler I'm using doesn't support {[3]='b'} style
    // array initialization, so we're gonna have to do this.
    morse_lookup[0b010000] = 'A';
    morse_lookup[0b100011] = 'B';
    morse_lookup[0b101011] = 'C';
    morse_lookup[0b100111] = 'D';
    morse_lookup[0b011111] = 'E';
    morse_lookup[0b001011] = 'F';
    morse_lookup[0b110111] = 'G';
    morse_lookup[0b000011] = 'H';
    morse_lookup[0b001111] = 'I';
    morse_lookup[0b011100] = 'J';
    morse_lookup[0b101000] = 'K';
    morse_lookup[0b010011] = 'L';
    morse_lookup[0b110000] = 'M';
    morse_lookup[0b101111] = 'N';
    morse_lookup[0b111000] = 'O';
    morse_lookup[0b011011] = 'P';
    morse_lookup[0b110100] = 'Q';
    morse_lookup[0b010111] = 'R';
    morse_lookup[0b000111] = 'S';
    morse_lookup[0b100000] = 'T';
    morse_lookup[0b001000] = 'U';
    morse_lookup[0b000100] = 'V';
    morse_lookup[0b011000] = 'W';
    morse_lookup[0b100100] = 'X';
    morse_lookup[0b101100] = 'Y';
    morse_lookup[0b110011] = 'Z';
    morse_lookup[0b011110] = '1';
    morse_lookup[0b001110] = '2';
    morse_lookup[0b000110] = '3';
    morse_lookup[0b000010] = '4';
    morse_lookup[0b000001] = '5';
    morse_lookup[0b100001] = '6';
    morse_lookup[0b110001] = '7';
    morse_lookup[0b111001] = '8';
    morse_lookup[0b111101] = '9';
    morse_lookup[0b111110] = '0';
    morse_lookup[0b000000] = ' ';
}

char morse_to_char(morse_key_t morse_key){
    if (morse_key_invalid(morse_key)) {
        return '?';
    }
    morse_key = morse_finalize(morse_key);
    return morse_lookup[morse_key] ? morse_lookup[morse_key] : '?';
}

morse_key_t morse_append_dit(morse_key_t morse_key){
    if (morse_key_invalid(morse_key)){
        return morse_key;
    }
    morse_key <<= 1;
    morse_key |= DIT;
    return morse_key;
}

morse_key_t morse_append_dah(morse_key_t morse_key){
    if (morse_key_invalid(morse_key)){
        return morse_key;
    }
    morse_key <<= 1;
    morse_key |= DAH;
    return morse_key;
}

morse_key_t morse_finalize(morse_key_t morse_key){
    if (morse_key < 0b1000000){
        uint8_t pad_val = morse_key & 1;
        pad_val = !pad_val;
        while(morse_key < 0b1000000){
            morse_key <<= 1;
            morse_key |= pad_val;
        }
    }
    return morse_key & 0b111111;
}