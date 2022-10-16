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
    typedef enum {LED_SET1, LED_SET2} LED_SET;


    private:
    DigitalInOut redLED;
    DigitalInOut yellowLED;
    DigitalInOut greenLED;

    int ledChoice=0;
    int ledFlag=0;

    Ticker t;
    LIGHT_STATE State;
    LED_SET chosenLEDS;
    microseconds flashInterval = 250ms; //Set default flash interval to 250 ms, causing it to flash 2 times per second

    void yellowFlashISR();
    void flashYellow(bool flash);
    void updateOutput();
    

    public:
    //Constructor
    //TrafficLight(PinName redPin = TRAF_RED2_PIN, PinName yellowPin = TRAF_YEL2_PIN, PinName greenPin=TRAF_GRN2_PIN, LED_SET _chosenLEDS=LED_SET2); //default

    //TrafficLight(PinName redPin = TRAF_RED2_PIN, PinDirection redDir=PIN_OUTPUT, PinMode redMode=OpenDrainNoPull, int redValue=0,PinName yellowPin = TRAF_YEL2_PIN, PinName greenPin=TRAF_GRN2_PIN); //typical constructor call

    TrafficLight(int ledChoice, PinName redPin = TRAF_RED1_PIN, PinName yellowPin = TRAF_YEL1_PIN, PinName greenPin=TRAF_GRN1_PIN); //typical constructor call

    TrafficLight(PinName redPin = TRAF_RED2_PIN, PinName yellowPin = TRAF_YEL2_PIN, PinName greenPin=TRAF_GRN2_PIN); //typical constructor call

    //TrafficLight(PinName redPin, PinName yellowPin, PinName greenPin, int ledChoice=0); //typical constructor call

    //Destructor
    ~TrafficLight();

    //Advance the traffic lights to the next state
    LIGHT_STATE nextState();

    void stop();
    void setFlashSpeed(double);
    double getFlashSpeed();

};


#endif