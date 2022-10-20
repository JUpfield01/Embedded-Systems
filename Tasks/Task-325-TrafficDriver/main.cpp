#include "mbed.h"
#include "TrafficLight.h"

//TrafficLight lights1(); //Initalise Traffic light set using led choice defined in TrafficLight.h
TrafficLight lights2, lights1(2); //Initalise Traffic light set using led choice defined in TrafficLight.h

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
        s = lights1.nextState();
        s2 = lights2.nextState();

        //Debounce switch
        wait_us(300000);

        //Wait for switch release
        while (sw==1);

        //Switch debounce
        wait_us(300000);

        printf("\nled flash speed: %f ms",lights1.getFlashSpeed());

        count++;

    }
}

