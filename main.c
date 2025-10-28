//#include "tm4c123gh6pm.h"
#include <stdint.h>



uint32_t fadd(uint32_t a, uint32_t b){

    uint8_t e1,e2,e;
    uint32_t m1,m2,m, result;

    e1 = (a >> 23) & 0xFF;
    e2 = (b >> 23) & 0xFF;

    m1 = a & 0x7FFFFF | 0x800000;
    m2 = b & 0X7FFFFF | 0x800000;


    if(e1 == e2){
        e = e1;
    }
    else if (e1 < e2){
        uint8_t shift = e2 - e1;
        m1 = m1 >> shift;
        e2 = e1;
    }
    else if (e2 < e1){
        uint8_t shift = e1 - e2;
        m2 = m2 >> shift;
        e1 = e2;
    }
    e = e1;
    m = m1 + m2;

    if (m & 0x1000000) { // overflow beyond 24 bits
            m >>= 1;
            e++;
        }
    else {
            while ((m & 0x800000) == 0 && e > 0) {
                m <<= 1;
                e--;
            }
        }
    result = (0 << 31) | (e << 23) | (m & 0x7FFFFF);
    return result;

}
int main(void) {
    uint32_t x,y;
    x = 0x41C80000;
    y = 0x3DCCCCCD;
    uint32_t result = fadd(x,y);
    while (1) {
        // Do nothing, everything handled in ISR
    }
}

