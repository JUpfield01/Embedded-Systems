#include "mbed.h"
#include "uop_msb.h"
//#include "F429_Mega_Shell_Header.h"

using namespace std;

void matrix_scan();
void clearMatrix();

int main() {
    while (true) {
        matrix_scan();
    }
}





/*
void matrix_scan(void)
{
    while(true)
    {
        for (int j=0;j<=7;j++)  //NB ROW has 3 to 8 decoder so 0 to 7 to Row Select
                                //COLUMNS(COL) are 0 to 255 to select each Byte
        {
            for (int i=1;i<255;i*=2) //Increment LEFT Hand Block of 8
            {
                cs=0;           //Send Data to Matrix
                spi.write(0x00);//COL RHS
                spi.write(i);   //COL LHS
                spi.write(j);   //ROW RHS
                cs=1;           //low to high will effectivelly LATCH the Shift register to output
                thread_sleep_for(SCAN_RATE_MS);
            }
            for (int i=1;i<255;i*=2) //Increment RIGHT Hand Block of 8
            {
                cs=0;           //Send Data to Matrix
                spi.write(i);   //COL RHS
                spi.write(0x00);//COL LHS
                spi.write(j);   //ROW RHS
                cs=1;           //low to high will effectivelly LATCH the Shift register to output
                thread_sleep_for(SCAN_RATE_MS);
            }
        }
    for (int j=0;j<=7;j++)  //NB ROW has 3 to 8 decoder so 0 to 7 to Row Select
                                //COLUMNS(COL) are 0 to 255 to select each Byte
        {
            {
                cs=0;           //Send Data to Matrix
                spi.write(0xFF);//COL RHS
                spi.write(0xFF);   //COL LHS
                spi.write(j);   //ROW RHS
                cs=1;           //low to high will effectivelly LATCH the Shift register to output
                thread_sleep_for(SCAN_RATE_MS);
            }
        }
     for (int j=7;j>=0;j--)  //NB ROW has 3 to 8 decoder so 0 to 7 to Row Select
                                //COLUMNS(COL) are 0 to 255 to select each Byte
        {
            {
                cs=0;           //Send Data to Matrix
                spi.write(0xFF);//COL RHS
                spi.write(0xFF);   //COL LHS
                spi.write(j);   //ROW RHS
                cs=1;           //low to high will effectivelly LATCH the Shift register to output
                thread_sleep_for(SCAN_RATE_MS);
            }
        }

    }
}


void clearMatrix(void)
{
    cs=0;           //CLEAR Matrix
    spi.write(0x00);//COL RHS
    spi.write(0x00);//COL LHS
    spi.write(0x00);//ROX RHS
    cs=1;
}
*/