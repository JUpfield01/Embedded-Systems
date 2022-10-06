#include "uop_msb.h"
using namespace uop_msb;

Buzzer buzz;

DigitalOut led1(LED1);
DigitalOut led2(LED2);
DigitalOut led3(LED3);


int main()
{
    printf("\nTASK-112\n");
    while(true){

        BufferedSerial pc(USBTX, USBRX);
        pc.set_blocking(false);

        char c;
        ssize_t result = pc.read(&c, 1);

        printf("read returned the value %d\n", result);
        printf("Read: %c\n", c);

        if (result == -EAGAIN) {
            printf("No data in buffer\n");
        }   
    } 
}