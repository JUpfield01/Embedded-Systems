#include "uop_msb.h"
#include "PushSwitch.hpp"

#include <chrono>
#include <cstdint>
#include <cstdio>
using namespace uop_msb;

Semaphore sem1(5); // Set size to 5 as we want to count 0..10 The starting value is 5 so we need to go 5 below it to reach 0
Semaphore sem2(5); // Set size to 5 as need to count to 10 and the start value is 5. sem2 is used to count up and sem1 down, hence why each is set in the way it is.
Mutex countLock;
uint16_t counter = 5;
Thread t1;
Thread t2;

void climb()
{
    PushSwitch sw(BTN1_PIN);
    DigitalOut led(LED1);

    while (true) {
        sw.waitForPress(); //Blocking

        led = 1;
        sem2.acquire(); //Decrement
        countLock.lock();
        counter++;
        printf("%u\n", counter);
        countLock.unlock();
        sem1.release(); //Increment
        led = 0;

        //Debounce
        ThisThread::sleep_for(50ms);
        sw.waitForRelease();
        ThisThread::sleep_for(50ms);
    }
}

void descend()
{
    PushSwitch sw(BTN2_PIN);
    DigitalOut led(LED2);

    while (true) {
        sw.waitForPress(); //Blocking

        led = 1;
        sem1.acquire(); //Decrement
        countLock.lock();
        counter--;
        printf("%u\n", counter);
        countLock.unlock();
        sem2.release(); //Increment
        led = 0;

        //Debounce
        ThisThread::sleep_for(50ms);
        sw.waitForRelease();
        ThisThread::sleep_for(50ms);        
    }
}

int main(void)
{
    DigitalOut led(LED3);
    t1.start(climb);
    t2.start(descend);

    while (true) {
        ThisThread::sleep_for(1000ms);
        led = !led;
    }
    
}   