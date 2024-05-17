#include "stm32f446xx.h"
#include "core_cm4.h"

void __io_putchar(char c){
    ITM_SendChar(c);
}