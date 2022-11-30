#include "mbed.h"
#include "uop_msb.h"
#include <iostream>
#include "PressAndRelease.hpp"

using namespace uop_msb;
using namespace std;

//Globals
DigitalOut led1(LED1);
DigitalOut led2(LED2);

//Thread to handle terminal output
Thread t2; 

//Event queue for main
EventQueue mainQueue;
EventQueue t2Queue; 


//Flash a given LED - parameter passed by reference
void flashLed(DigitalOut& led) {
    led = !led;
}
 
void flashLed1() {
    // This is NOT on the main thread
    mainQueue.call(flashLed, led1);                         
    //Dispatch printf on main thread
    t2Queue.call(printf, "Button A\n");    
}

void flashLed2() {
    mainQueue.call(flashLed, led2);    
    t2Queue.call(printf, "Button B\n");
}

void task2() {
    t2Queue.dispatch_forever();

    while (true) {

    }
}

void printButton() {
    printf("Button Pressed: \n");
}

int main() {

    printf("Starting Main...\n");

    t2.start(task2);
    t2.set_priority(osPriorityLow);

    PressAndRelease btnA(BTN1_PIN, &flashLed1);
    PressAndRelease btnB(BTN2_PIN, &flashLed2);

    //Start main queue - dispatch
    mainQueue.dispatch_forever();
}









