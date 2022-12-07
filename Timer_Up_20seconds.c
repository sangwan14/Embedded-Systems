#include <msp430.h>

#define RED_LED 0x0001
#define DEVELOPMENT 0x5A80
#define ENABLE_PINS 0xFFFE
#define ACLK 0x0100
#define UP 0x0001
#define TAIFG 0x0001

main() {
    unsigned char intervals = 0;
    WDTCTL = DEVELOPMENT;
    PM5CTL0 = ENABLE_PINS;

    TA0CCR0 = 50000;
    TA0CTL = ACLK | UP;

    P1DIR = RED_LED;
    P1OUT = RED_LED;

    while(1) {
        if(TA0CTL & TAIFG){
            intervals += 1;
            TA0CTL = TA0CTL & (~TAIFG);

            if(intervals == 16){
                intervals = 0;
                P1OUT &= ~RED_LED;
            }
        }
    }
}
