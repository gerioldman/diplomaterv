#include "opentestloader_struct.h"

extern opentestloader_struct opentestloader;

void putchar_(char c);

void putchar_(char c){
    opentestloader.send_char(c);
}