#include "uart_ee627.h"
#include <stdint.h>

int main(void) {
    UART_setup(); // Initialize UART0

    while(1) {
        UART_send(0x55);  // Send 0x55
        for(volatile int i = 0; i < 1000000; i++);  // Small delay
        UART_send(0xAA);  // Send 0xAA
        for(volatile int i = 0; i < 1000000; i++);  // Small delay
    }
}
