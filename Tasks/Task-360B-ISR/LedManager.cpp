#include "LedManager.h"

LedManager::LedManager(PinName ledPin) : led(ledPin=TRAF_YEL1_PIN) {
    led=0;

}

void LedManager::ledFlashISR() {
    led =  !led;
}

void LedManager::flashLed(bool flash) {
    ledTimer.detach();
    if (flash) {
        ledTimer.attach(callback(this, &LedManager::ledFlashISR), 500ms);
    }
    else {
        led=0;
    }
    
}

