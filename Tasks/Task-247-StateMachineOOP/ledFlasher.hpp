#include "mbed.h"
#include <chrono>
#include <ratio>

using namespace std::chrono;

class ledFlasher {

    private:
    DigitalOut led;
    Timer ledTmr;
    microseconds flashInterval=0ms;
    microseconds currentTime=0ms;

    public:

        ledFlasher(PinName ledPin, microseconds flashDuration) : led(ledPin), flashInterval(flashDuration) {
            ledTmr.start();
            led=0;
        }

        void flashLed() {
            currentTime = ledTmr.elapsed_time();
            if (currentTime >= flashInterval) {
                led=!led;
                ledTmr.reset();
                currentTime=0ms;
            }
        }

};


