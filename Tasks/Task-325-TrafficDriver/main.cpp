#include "mbed.h"
#include "TrafficLight.h"


TrafficLight PUSH_PULL_LEDS(TrafficLight::LIGHT_SET::PUSH_PULL); 
TrafficLight OPEN_DRAIN_LEDS(TrafficLight::LIGHT_SET::OPEN_DRAIN); 

DigitalIn sw(USER_BUTTON);

TrafficLight::LIGHT_STATE s;

TrafficLight::LIGHT_STATE s2;

int main()
{

    int count = 0;

    while (true) {

        /*
        if(count>10) {
            lights1.setFlashSpeed(100);
            if(count>100){
                count=0;
            }
        }
        */

        //Wait for switch press
        while (sw==0);

        //Update lights
        s = PUSH_PULL_LEDS.nextState();
        s2 = OPEN_DRAIN_LEDS.nextState();

        //Debounce switch
        wait_us(300000);

        //Wait for switch release
        while (sw==1);

        //Switch debounce
        wait_us(300000);

        printf("\nled flash speed: %f ms",PUSH_PULL_LEDS.getFlashSpeed());

        count++;

    }
}

