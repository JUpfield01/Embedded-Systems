#include "uop_msb.h"
#include "mbed.h"
#include <chrono>
#include <ratio>
using namespace uop_msb;
using namespace chrono;

//Buzzer
Buzzer buzz;

// Create a DigitalOutput object to toggle an LED whenever data is received.
static DigitalOut led1(LED1);
static DigitalOut led2(LED2);

// Create a UnbufferedSerial object with a default baud rate.
static UnbufferedSerial serial_port(USBTX, USBRX);

//Ticker
Ticker ledTicker;

//Flash rate (us)
volatile long long T = 500000;

char prevChar;
int strChecker=0;

//ISR for flashing blue LED
void onTick()
{
    led2 = !led2;
}

void on_rx_interrupt()
{
    CriticalSectionLock lock;
    char p;

    // Read the data to clear the receive interrupt.
    if (serial_port.read(&p, 1)) {

        //p=toLower(p);
        //Check the character input
        switch (p) {
        case 13:
            //User pressed return
            serial_port.write("\n\r",2); //Echo a newline
            strChecker=0;
            break;

        case '1':
            //Switch on buzzer
            buzz.playTone("A");
            strChecker=0;
            break;

        case '2':
            //Switch off buzzer
            buzz.rest();
            strChecker=0;
            break;

        case '+':
            T += 100000;
            ledTicker.detach();
            ledTicker.attach(&onTick, microseconds(T));
            strChecker=0;
            break;

        case '-':
            if (T >= 200000) {
                T -= 100000;
                ledTicker.detach();
                ledTicker.attach(&onTick, microseconds(T));
            }
            strChecker=0;
            break;

        case 'u':
        case 'U':
        //case 'P':
            strChecker=2;
            //led1 = !led1;
            break; 

        case 'p':
        case 'P':
        //case 'P':
            if((prevChar=='u'||'U')&&(strChecker==2)) {
                T += 100000;
                ledTicker.detach();
                ledTicker.attach(&onTick, microseconds(T));
            }  
            strChecker=0;
            break; 

        case 'd':
        case 'D':
                strChecker=1;
                //led1 = !led1;
            break;

        case 'o':
        case 'O':
            if((prevChar=='d'||'D')&&(strChecker==1)) {
                strChecker=1;
                //led1 = !led1;
            }
            else {
                strChecker=0;
            }
            break;

        case 'w':
        case 'W':
            if((prevChar=='o'||'O')&&(strChecker==1)) {
                strChecker=1;
                //led1 = !led1;
            }
            else {
                strChecker=0;
            }
            break;

        case 'n':
        case 'N':
            if((prevChar=='w'||'W')&&(strChecker==1)) {
                //led1 = !led1;
                if (T >= 200000) {
                    T -= 100000;
                    ledTicker.detach();
                    ledTicker.attach(&onTick, microseconds(T));
                }
            }
            strChecker=0;
            break;

        default:
            //Echo typed character to the terminal
            strChecker=0;
            break;
        };
        serial_port.write(&p,1);
        prevChar=p;
    }

    // Toggle the LED.
    led1 = !led1; 
}

LCD_16X2_DISPLAY disp;




int main(void)
{
    // Set desired properties (115200-8-N-1).
    serial_port.baud(115200);
    serial_port.format(

        /* bits */ //8,
        /* parity */ //SerialBase::None,
        /* stop bit */ //1


    );

    // Register a callback to process a Rx (receive) interrupt.
    serial_port.attach(&on_rx_interrupt, SerialBase::RxIrq);

    //ISR to flash led
    CriticalSectionLock::enable();
    ledTicker.attach(&onTick, microseconds(T));
    CriticalSectionLock::disable();

    while (true) {
        sleep(); 
        disp.cls();
        disp.locate(1,1);
        disp.printf("T=%Ldms", T/1000);
        disp.locate(2,1);
        disp.printf("str: %c", prevChar);
        disp.locate(2,8);
        disp.printf("str: %d", strChecker);
        //printf("T=%Ldms", T);    
    }
    
}


/*
int main(void)
{
    while(true) {
        printf("Test\n");
        wait_us(1000000);
    }
    
}

*/