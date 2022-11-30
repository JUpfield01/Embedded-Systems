#include "uop_msb.h"
#include <chrono>
#include <cstdlib>
using namespace uop_msb;

#include "sample_hardware.hpp"

#include "string.h"
#include <stdio.h>
#include <ctype.h>

#define SWITCH1_RELEASE 1

void thread1();
void thread2();
void switchISR();

//Threads
Thread t1;

struct angleData {
    float xAngle;
    float yAngle;
    float zAngle;
};

//Queues - "A message can be a integer or pointer value  to a certain type T that is sent to a thread or interrupt service routine."
Queue<angleData, 10> queue;

//Timeout time (1s)
const uint32_t TIMEOUT_MS = 1000;

// Call this on precise intervals
void ISR() {
    
    //Option to starve the queue of data
    if (buttonA == 1) return;
    
    //Random sample
    angleData sample;
    sample.xAngle=0.01*(rand()%100);
    sample.yAngle=0.01*(rand()%100);
    sample.zAngle=0.01*(rand()%100);

    //uint32_t sample = rand();

    angleData* msg = &sample;
    
    //Write to queue as 32-bit integer (same size as pointer)
    bool sent = queue.try_put(msg); //Non-blocking
    
    //Check if succesful
    if (sent) {
         //If successfully sent kick watchdog to prevent timeout
        Watchdog::get_instance().kick();
    }
    else {
        //If not sent then buffer is full, toggle red led and let watchdog reset device
       redLED = 1;
    }
}

//Normal priority thread (consumer)
void thread1() 
{    
    while (true) {
        //Read queue - block (with timeout)
        angleData* rx;   // Fancy type for a 32-bit integer :)
        bool success = queue.try_get_for(10s, &rx); //Blocks for 10s if there is no data
        
        angleData &test = *rx;

        float poop = test.xAngle;
        //float poop = 5;

        if (success) {
            printf("value: %f\n", rx->xAngle);
        } else {
            printf("Receive timeout\n");
            yellowLED = 1;
        }
                
        //Block up consumer if switch is held down
        //Will fill the queue if held long enough
        while (buttonB == 1);
        
    } //end while
}


// Main thread
int main() {
    post();

    //Start message
    printf("Welcome\n");
           
    //Hook up timer interrupt   
    Ticker timer; 
    timer.attach(&ISR, 1s);
               
    //Threads
    t1.start(thread1);

    //Create & start watchdog
    Watchdog &watchdog = Watchdog::get_instance();
    watchdog.start(TIMEOUT_MS);
    fflush(stdout);
    
    printf("Main Thread\n");
    while (true) {
        ThisThread::sleep_for(500ms);
        greenLED = !greenLED;
        
    }
}
