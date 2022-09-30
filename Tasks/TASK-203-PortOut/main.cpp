#include "mbed.h"

// Hardware Definitions
#define TRAF_GRN1_PIN PC_6
#define TRAF_YEL1_PIN PC_3
#define TRAF_RED1_PIN PC_2

#define TRAF_GRN2_PIN PB_0
#define TRAF_YEL2_PIN PB_7
#define TRAF_RED2_PIN PB_14

#define LEDMASK 0b0000000001001100 
#define LEDMASK2 0b0100000010000001 

// Objects
//BusOut leds(TRAF_RED1_PIN, TRAF_YEL1_PIN, TRAF_GRN1_PIN);
PortOut leds(PortC, LEDMASK);
PortOut obleds(PortB, LEDMASK2);

int main()
{
    while (true) {
        /*
        leds = 0;   //Binary 000
        obleds = 0;
        wait_us(500000);
        leds = 0xFF;   //Binary 11111111
        obleds = 0xFFFF; // Ensure that values written for 16 bits not 8 bits as writing to PB_14
        wait_us(500000);  
        */

        leds = leds ^  LEDMASK;
        wait_us(500000); 
    }
}




