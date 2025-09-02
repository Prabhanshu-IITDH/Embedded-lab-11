#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"

#define STCTRL *((volatile long *) 0xE000E010)
#define STRELOAD *((volatile long *) 0xE000E014)
#define STCURRENT *((volatile long *) 0xE000E018)

#define COUNT_FLAG (1<<16)
#define ENABLE (1<<0)
#define CLKINT (1<<2)
#define CLOCK_MHZ_16


void delay(int ms){
    int t = 16000*ms;
    STRELOAD = t;
    STCURRENT = 0;
    STCTRL = (CLKINT | ENABLE);
    while ((STCTRL & COUNT_FLAG)==0){
        // Do nothing
    }
    STCTRL = 0;

}

int main(void)
{
    SYSCTL_RCGC2_R |= 0x20;            // Enable clock to Port F
    GPIO_PORTF_LOCK_R = 0x4C4F434B;    // Unlock PF0
    GPIO_PORTF_CR_R   = 0x1F;          // Commit PF0�PF4
    GPIO_PORTF_DEN_R  = 0x1F;          // Digital enable PF0�PF4
    GPIO_PORTF_DIR_R  = 0x0E;          // PF1,PF3 output (LEDs), PF0 & PF4 input
    GPIO_PORTF_PUR_R  = 0x11;          // Enable pull-up on PF0 & PF4


    while(1)
    {
        delay(500);
        GPIO_PORTF_DATA_R = 0x02;
        delay(500);
        GPIO_PORTF_DATA_R = 0x00;

    }
}
