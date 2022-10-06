#include "uop_msb.h"
using namespace uop_msb;

// Hardware Definitions
#define TRAF_RED1_PIN PC_2

// Inputs
DigitalIn SW_BLUE(USER_BUTTON);

// Outputs
DigitalOut ledRed(TRAF_RED1_PIN,0);

// Timer(modified version from Timer)
TimerCompat tmr1;

int main()
{
    //Time how long it takes to perform a printf
    tmr1.start();
    printf("Hello World How Are You\n");
    tmr1.stop();

    //Print out how long it took
    unsigned long long dur = tmr1.read_ms();
    printf("The time taken was %llu milliseconds\n", dur);    

    //Now to use a timer to implement a delay
    tmr1.start();
    while (true) {
        //Wait for switch press
        while (SW_BLUE == 0);

        //tmr1.reset();
        //while (tmr1.elapsed_time() < 50ms);
        wait_us(50000);

        while (SW_BLUE == 0);

        //Turn on LED
        ledRed = !ledRed;

        while (SW_BLUE == 1);

        //Wait for 500ms
        //tmr1.reset();
        //while (tmr1.elapsed_time() < 50ms); //How about this for C++ magic :)
        wait_us(50000);


    }
}



