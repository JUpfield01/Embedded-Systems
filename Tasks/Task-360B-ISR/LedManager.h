#include "mbed.h"

#define TRAF_YEL1_PIN PC_3

class LedManager {

private:
DigitalOut led;
Ticker ledTimer; 

void ledFlashISR();


public:
    LedManager(PinName ledPin=TRAF_YEL1_PIN);

    ~LedManager();

    void flashLed(bool flash);


};



