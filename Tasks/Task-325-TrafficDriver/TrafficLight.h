#ifndef __TRAFFICLIGHT__
#define __TRAFFICLIGHT__

#include "mbed.h"
#include <chrono>
using namespace chrono;

#define TRAF_GRN1_PIN PC_6
#define TRAF_YEL1_PIN PC_3
#define TRAF_RED1_PIN PC_2

#define TRAF_GRN2_PIN PC_9
#define TRAF_YEL2_PIN PC_8
#define TRAF_RED2_PIN PC_7



class TrafficLight 
{
    public:
    typedef enum {STOP, READY, GO, WARNING} LIGHT_STATE;
    typedef enum {PUSH_PULL, OPEN_DRAIN} LIGHT_SET;


    private:
    DigitalInOut redLED;
    DigitalInOut yellowLED;
    DigitalInOut greenLED;

    Ticker t;

    LIGHT_STATE State;

    microseconds flashInterval = 250ms; //Set default flash interval to 250 ms, causing it to flash 2 times per second

    int ledFlag=0;

    void yellowFlashISR();
    void flashYellow(bool flash);
    void updateOutput();
    

    public:
    

    //Constructor
    TrafficLight(LIGHT_SET ledChoice);

    //Destructor
    ~TrafficLight();

    //Advance the traffic lights to the next state
    LIGHT_STATE nextState();

    void stop();
    void setFlashSpeed(double);
    double getFlashSpeed();

};


#endif