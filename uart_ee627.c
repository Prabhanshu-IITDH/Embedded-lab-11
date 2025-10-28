#include "uart_ee627.h"
#include "tm4c123gh6pm.h"  // Device header file

void UART_setup(void) {
    SYSCTL_RCGCUART_R |= (1 << 0);   // UART0 clock enable
    SYSCTL_RCGCGPIO_R |= (1 << 0);   // Port A clock enable

    // Wait for peripherals to be ready
    while((SYSCTL_PRGPIO_R & (1 << 0)) == 0);
    while((SYSCTL_PRUART_R & (1 << 0)) == 0);

    // 2. Configure PA0 (U0RX) and PA1 (U0TX)
    GPIO_PORTA_AFSEL_R |= 0x03;      // Enable alternate function on PA0, PA1
    GPIO_PORTA_PCTL_R &= ~0xFF;      // Clear PCTL for PA0, PA1
    GPIO_PORTA_PCTL_R |= 0x11;       // Configure PCTL: PA0 -> U0RX, PA1 -> U0TX
    GPIO_PORTA_DEN_R  |= 0x03;       // Enable digital I/O on PA0, PA1
    GPIO_PORTA_AMSEL_R &= ~0x03;     // Disable analog on PA0, PA1

    
    UART0_CTL_R &= ~(1 << 0);

    UART0_IBRD_R = 104;
    UART0_FBRD_R = 11;  

    
    UART0_LCRH_R = (0x3 << 5); 

    
    UART0_CTL_R |= (1 << 0) | (1 << 8) | (1 << 9);
}

void UART_send(uint8_t data) {
    
    while((UART0_FR_R & (1 << 5)) != 0);
    
    UART0_DR_R = data;
}
