#include <stdint.h>
#include <stdbool.h>
#include "tm4c123gh6pm.h"
/**
 * main.c
 */
int main(void)
{
    SYSCTL_RCGC2_R |=   0x00000020;      // ENABLE CLOCK TO GPIOF
    GPIO_PORTF_LOCK_R = 0x4C4F434B;      // UNLOCK COMMIT REGISTER
    GPIO_PORTF_CR_R   = 0x1F;            // MAKE PORTF0 CONFIGURABLE
    GPIO_PORTF_DEN_R  = 0x1F;            // SET PORTF PINS 4 PIN
    GPIO_PORTF_DIR_R  = 0x0E;            // SET PORTF4 PIN AS INPUT USER SWITCH PIN
    GPIO_PORTF_PUR_R  = 0x11;            // PORTF4 IS PULLED UP

    while(1)
    {
        GPIO_PORTF_DATA_R = 0x0;
        if (!(GPIO_PORTF_DATA_R & 0x01) && (GPIO_PORTF_DATA_R & 0x10) ){
            GPIO_PORTF_DATA_R = 0x02;
        }
        else if (!(GPIO_PORTF_DATA_R & 0x10) && (GPIO_PORTF_DATA_R & 0x01)){
                    GPIO_PORTF_DATA_R = 0x04;
                }
        else if (!(GPIO_PORTF_DATA_R & 0x10) && !(GPIO_PORTF_DATA_R & 0x01)){
                            GPIO_PORTF_DATA_R = 0x06;
                        }
        else GPIO_PORTF_DATA_R = 0x00;
    }
}