#include "uop_msb.h"
using namespace uop_msb;

// Inputs
DigitalIn SW2(BTN1_PIN);
DigitalIn SW3(BTN2_PIN);

// Outputs
DigitalOut ledRed(TRAF_RED1_PIN);
DigitalOut ledYel(TRAF_YEL1_PIN);
DigitalOut ledGrn(TRAF_GRN1_PIN);

// Timers (modified version from Timer)
TimerCompat tmr_flash;
TimerCompat tmr_debounceSW2;
TimerCompat tmr_debounceSW3;


// Function to check flash timer and reset if being flashed.
void tmr_flash_read()
{
    if(tmr_flash.read_ms()>=500)
        {
            ledYel = !ledYel;
            tmr_flash.reset();
        }
}

int main()
{
    int SW2val=0, SW3val=0;
    int prev_SW2val=0, prev_SW3val=0;
    //Start flashing timer
    tmr_flash.start();

    while (true) {

        tmr_flash_read();
        SW2val = SW2;
        SW3val = SW3;

        if(prev_SW2val != SW2val)
        {
            tmr_debounceSW2.start();
                if(tmr_debounceSW2.read_ms()>=50&&prev_SW2val==1)
                {
                    ledRed = !ledRed;
                    tmr_debounceSW2.reset();
                }
        }

        if(prev_SW3val != SW3val)
        {
            tmr_debounceSW3.start();
                if(tmr_debounceSW3.read_ms()>=50&&prev_SW3val==1)
                {
                    ledGrn = !ledGrn;
                    tmr_debounceSW3.reset();
                }
        }

        prev_SW2val = SW2val;
        prev_SW3val = SW3val;
    }
}





