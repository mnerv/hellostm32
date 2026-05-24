#include <stddef.h>
#include <stdint.h>

#include "morse.h"

static char const *const MORSE_TABLE[26] = {
    ".-",   "-...", "-.-.", "-..",  ".",    // A-E
    "..-.", "--.",  "....", "..",   ".---", // F-J
    "-.-",  ".-..", "--",   "-.",   "---",  // K-O
    ".--.", "--.-", ".-.",  "...",  "-",    // P-T
    "..-",  "...-", ".--",  "-..-", "-.--", // U-Y
    "--..",                                 // Z
};

char const *morse_encode(char c) {
    if (c >= 'a' && c <= 'z') c = (char)(c - 'a' + 'A');
    if (c < 'A' || c > 'Z') return NULL;
    return MORSE_TABLE[(uint8_t)(c - 'A')];
}
