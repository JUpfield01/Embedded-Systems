#include "TrafficLight.h"

using namespace chrono;

/*
//Constructor
//TrafficLight::TrafficLight(PinName redPin, PinName yellowPin, PinName greenPin, LED_SET) : redLED(redPin), yellowLED(yellowPin), greenLED(greenPin)
TrafficLight::TrafficLight(PinName redPin, PinName yellowPin, PinName greenPin, LED_SET _chosenLEDS) : redLED(redPin), yellowLED(yellowPin), greenLED(greenPin)
{
    //redPin=TRAF_RED1_PIN;
    //yellowPin=TRAF_YEL1_PIN;
    //greenPin=TRAF_GRN1_PIN;

    if(_chosenLEDS==LED_SET1) {
        printf("\nLed set 1 initalised");
    }

    else if (_chosenLEDS==LED_SET2) {
        redPin=TRAF_RED2_PIN;
        yellowPin=TRAF_YEL2_PIN;
        greenPin=TRAF_GRN2_PIN;
        printf("\nredPin: %d", redPin);
        printf("\nLed set 2 initalised");
    }

    else{
        printf("ERROR: Argument type not found - TrafficLight(LED_SET)");
    }


    // These objects are already initialised in the member initialisation list above  
    redLED = 1;
    yellowLED = 0;
    greenLED = 0;
    // Timer off
    flashYellow(false);
}

*/

//TrafficLight::TrafficLight(PinName redPin, PinDirection redDir, PinMode redMode, int redValue, PinName yellowPin, PinName greenPin) 

TrafficLight::TrafficLight(int ledChoice, PinName redPin, PinName yellowPin, PinName greenPin) : redLED(redPin),yellowLED(yellowPin), greenLED(greenPin)
{
    // These objects are already initialised in the member initialisation list above
    redLED.output();
    yellowLED.output();
    greenLED.output();

    redLED = 1;
    yellowLED = 0;
    greenLED = 0;
    // Timer off
    flashYellow(false);
}

TrafficLight::TrafficLight(PinName redPin, PinName yellowPin, PinName greenPin) : redLED(redPin),yellowLED(yellowPin), greenLED(greenPin)
{
    // These objects are already initialised in the member initialisation list above
    redLED.output();
    yellowLED.output();
    greenLED.output();

    redLED.mode(OpenDrainNoPull);
    yellowLED.mode(OpenDrainNoPull);
    greenLED.mode(OpenDrainNoPull);


    ledFlag=1;
    redLED = 1;
    yellowLED = 1;
    greenLED = 0;
    // Timer off
    flashYellow(false);
}

//Destructor
TrafficLight::~TrafficLight()
{
    redLED = 1;
    yellowLED = 0;
    greenLED = 0;
    if(ledFlag==1) {
        redLED = 0;
        yellowLED = 1;
        greenLED = 1;
    }
} 

// Interrupt Service Routine (ISR)
void TrafficLight::yellowFlashISR() {
    yellowLED = !yellowLED;
}

// Private member function to switch flasher on or off
void TrafficLight::flashYellow(bool flash) {
    t.detach(); //Turn off ticker
    if (flash) {
        //Turn on ticker ..... Hmmm, interrupts!
        //t.attach(callback(this, &TrafficLight::yellowFlashISR), 200ms);
        t.attach(callback(this, &TrafficLight::yellowFlashISR), flashInterval);
    }
}

void TrafficLight::stop() {
    redLED = 1;
    yellowLED = 0;
    greenLED = 0; 

    if(ledFlag==1) {
        redLED = 0;
        yellowLED = 1;
        greenLED = 1;
    }

    printf("\nlights reset");
}

void TrafficLight::setFlashSpeed(double flashSpeed) {
    flashInterval=(int)flashSpeed*1ms; //Convert flashSpeed, not sure as to why the task requires flashSpeed to be a double?
}

double TrafficLight::getFlashSpeed() {
    double flashSpeed = 1000*duration<double>(flashInterval).count(); //Convert from microseconds to milliseconds and output as double
    return flashSpeed;
}

// Moore Machine - update outputs
void TrafficLight::updateOutput()
{
    switch (State)
    {
        case STOP:                  // STOP & GO
            if(ledFlag==1) {
                flashYellow(false);
                redLED = 1;
                yellowLED = 1;
                greenLED = 0;
            }
            else {
                flashYellow(false);
                redLED = 1;
                yellowLED = 0;
                greenLED = 0;
            }
            break;

        case READY:
            if(ledFlag==1) {
                redLED = 1;
                flashYellow(true);
                greenLED = 1;
            }
            else {
                flashYellow(false);
                redLED = 1;
                yellowLED = 1;
                greenLED = 0;
            }
            break;

        case GO:
            if(ledFlag==1) {
                flashYellow(false);
                redLED = 0;
                yellowLED = 1;
                greenLED = 1;
            }
            else {
                flashYellow(false);
                redLED = 0;
                yellowLED = 0;
                greenLED = 1;
            }
            break;

        case WARNING:

            if(ledFlag==1) {
                flashYellow(false);
                redLED = 0;
                yellowLED = 0;
                greenLED = 1;
            }
            else {
                redLED = 0;
                flashYellow(true);
                greenLED = 0;   
            }
            break;
                    
    }       
}

// Moore machine - next state logic
TrafficLight::LIGHT_STATE TrafficLight::nextState()
{
    // Update State
    switch (State)
    {
        case STOP:
            State = READY;
            break;
        case READY:
            State = GO;
            break;
        case GO:
            State = WARNING;
            break;
        case WARNING:
            State = STOP;
            break;
    }

    //As it says
    updateOutput();

    //Return the current state (for information)
    return State; 
} 