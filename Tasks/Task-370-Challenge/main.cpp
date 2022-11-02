#include "uop_msb.h"
#include <chrono>
#include <cstdint>
using namespace uop_msb;

Ticker ISR_Tick;
Thread t1;

void signalISR() {
    t1.flags_set(1); 
}


void task1(float* avg_) {
    
    int count = 0;
    float sum=0;

    printf("Task 1 Waiting to start\n"); 
    ThisThread::flags_wait_any(1); // Wait for timer ISR

    AnalogIn LDR(AN_LDR_PIN);  

    ThisThread::flags_clear(1);

    while(true) { 
        float &avg=*avg_; 

        if (count > 1000){
            //printf("\ncount reset, avg =%f\n",avg);
            //avg=0;
            count=0; // Reset count as 1000 samples collected
            sum=0;   // Resest sum as taking new samples
            printf("\nCount Reset");
        }

        ThisThread::flags_wait_any(1);

        //avg+=LDR.read();
        sum+= LDR.read(); 
        count ++;

        avg = sum/count;
    
        ThisThread::flags_clear(1);
    }
    
}


/*
1. Create an ISR - called by a Ticker every 1ms. This ISR simply has the job of signalling a waiting thread to perform an ADC conversion
2. Create a thread that waits for a signal from the ISR. This thread should ideally have the highest priority
3. Each time it is unblocked by the signal, it should read the ADC (Use `AnalogIn`) for the LDR and add it to a running sum.
4. Every 1s, it should print out the average of the past 1000 samples to the terminal. 
*/

// Done :^)

// Main

int main(void)
{

    float avg=0;

    t1.start(callback(task1, &avg));
    t1.set_priority(osPriorityRealtime); // No idea if it needs a priority this high but I can set it this high so I have. 
    ISR_Tick.attach(&signalISR, 1ms);

    while (true) {
        //printf("\n%f",avg/1000); // Weird bug when doing it this way, for some reason decays to 0 but after that is fine. 
        printf("\n%f",avg);
        ThisThread::sleep_for(1000ms);
    }
    
}   

