#include "mbed.h"

// Hardware Definitions
#define TRAF_GRN1_PIN PC_6
#define TRAF_YEL1_PIN PC_3
#define TRAF_RED1_PIN PC_2

// Objects
// DigitalOut grn(TRAF_GRN1_PIN);
// DigitalOut yel(TRAF_YEL1_PIN);
// DigitalOut red(TRAF_RED1_PIN,1);
BusOut leds(TRAF_RED1_PIN, TRAF_YEL1_PIN, TRAF_GRN1_PIN, PB_0, PB_7, PB_14);

int num, count, sum = 0;

int main()
{
    while (true) {
        /*
        leds = 0;   //Binary 000
        wait_us(500000);
        leds = 7;   //Binary 111
        wait_us(500000);    
        */

        //---Task 202.5---//
        /*
        for(int i=0; i<8; i++) 
        {
            leds = i;
            wait_us(500000);
        }
        */

        leds = 0;
        wait_us(500000);
        leds = 255;
        wait_us(500000);

    }
}


