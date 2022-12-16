/* mbed Microcontroller Library
 * Copyright (c) 2019 ARM Limited
 * SPDX-License-Identifier: Apache-2.0
 */

#include "mbed.h"
#include "F429_Mega_Shell_Header.h"
#include "TextLCD/TextLCD.h"
#include <cstdio>
#include <array>
//#include <cmath>

//prototypes
void Traffic_Lights();
void LCD_BackLight_Effect();
void Bar_Flash();
void clearMatrix();
void matrix_scan();
void matrix_bars();
int seg7num(int);
void seg7clear();
void count_thread();
float potav();
void environment_data();
int write_sdcard();
int read_sdcard();
void quantise(float values[32]);
void testSPI(int nums[2]);

EventQueue t3Queue;
EventQueue t4Queue;
EventQueue t5Queue;

Thread t1;
Thread t2;
Thread t3;
Thread t4;
Thread t5;
Thread t6;

Timer stopwatch;

struct matrixData {
    int leftSide[8]={0};
    int rightSide[8]={0};
};

void task3() {
    t3Queue.dispatch_forever();
}

void task4() {
    t4Queue.dispatch_forever();
}

void task5() {
    t5Queue.dispatch_forever();
}

void writeMatrix (matrixData matrixValues) {

    for (int i=0; i<8; i++) {
        cs=0;
        //int rhs=led_values_rhs[i];
        //int lhs=led_values_lhs[i];
        //int s_row=i;
        spi.write(matrixValues.rightSide[i]);
        spi.write(matrixValues.leftSide[i]);
        spi.write(i);
        //printf("right: %d\n", matrixValues.rightSide[i]);
        //printf("left: %d\n", matrixValues.leftSide[i]);
        //printf("%d\n", i);
        //printf("%d\n", led_values_rhs[i]);
        //printf("%d\n", led_values_lhs[i]);
        //printf("%d\n", i);
        //printf("\n");

        //spi.write(255);
        //spi.write(7);
        //spi.write(i);
        //printf("%d\n",i);
        cs=1;        
    }

}

int main()
{
    int nums[] = {255, 7};
    float values[32] = {0.483873, 1.625253, 0.839204, 0.869297, 0.897305, 1.004262, 0.623505, 0.480197, 1.089175, 0.653027, 0.929283, 0.618130, 0.577199, 0.606022, 0.773732, 0.874227, 0.588949, 0.805187, 0.714122, 0.701207, 0.589595, 0.691449, 0.514599, 0.679395, 0.756901, 0.468627, 0.786273, 0.596040, 0.736816, 0.432151, 0.389424, 0.234184};
    printf("\n\nstarting...\n");
    //write_sdcard();

  //  read_sdcard();

//printf("read second time\n");
        //read_sdcard();
    
    //seg7clear();

    //Traffic_Lights_2.output();
    //Traffic_Lights_2.mode(OpenDrainNoPull);
    //Traffic_Lights_2=1;

    //Pedestrian.output();
    //Pedestrian.mode(OpenDrainNoPull);

    //Pedestrian=0;
    //ThisThread::sleep_for(DELAY);//    wait_us(1000000);
    //Pedestrian=1;

    for(int i=0; i<32; i++) {
        printf("values @ %d: %f\n", i, values[i]);
    }

    // 7 segment display setup
    spi.format(8,0);            // 8bits, Rising edge, +VE Logic Data
    spi.frequency(1000000);     //1MHz Data Rate
    oe=0;                       //Enable Output NB can be more selective than this if you wish
    
    //char switchNum=' ';
    printf("Starting Program..\n");
    //t1.start(Traffic_Lights);
    //t2.start(LCD_BackLight_Effect);
    //t3.start(Bar_Flash);
    //t4.start(matrix_scan);
    t4.start(task4);
    t5.start(task5);

    t4Queue.call_every(2s, quantise, values);
    //t4.start(matrix_bars);
    //t5.start(count_thread);
    //t6.start(environment_data);

    //myLCD.cls();
    //myLCD.printf("SECaM PU");
    //myLCD.locate(0,1);myLCD.printf("Switch=");
    //buzzer.period_us(2273);
    //buzzer=0.5f;wait_us(200000);buzzer=0;
/*
    while(true){
        if (swA)switchNum='A';
        if (swB)switchNum='B';
        if (swC)switchNum='C';
        if (swD)switchNum='D';
        switch(switchNum){
            case 'A': buzzer.period_us(350);buzzer=0.5f;break;//spk.period_us(2273);
            case 'B': buzzer.period_us(360);buzzer=0.5f;break;//spk.period_us(2024);
            case 'C': buzzer.period_us(370);buzzer=0.5f;break;//spk.period_us(1912);
            case 'D': buzzer.period_us(380);buzzer=0.5f;break;//spk.period_us(1704);
            default:switchNum=' ';buzzer=0;break;
        }
        //Voltage = 3.3f * Pot_AN_INPUT.read();
        myLCD.locate(7, 1);myLCD.printf("%c",switchNum);
        myLCD.locate(10,1);myLCD.printf("%4.2fV",potav());
        //spk=0;
        switchNum=0;
        wait_us(200000);
    }
    */
    /*
    while (true) {
        quantise(&values[0]);
        //testSPI(&nums[0]);
    };
    */
}


float potav(){
    unsigned int adc_sample[SAMPLES+1];
    float Voltage;
    adc_sample[0]=0;
    for(int i=1; i<=SAMPLES; i++){
        adc_sample[i] = pot_an_input.read_u16();
        adc_sample[0]+=adc_sample[i];
    }
    Voltage = 3.3f * ((float)adc_sample[0]/(float)SAMPLES)/65535.0f;
    return Voltage;
}

void LCD_BackLight_Effect(){
    for(float i=0; i<1.0f; i+=0.01){
        myLCD_BL=i;
        ThisThread::sleep_for(20ms);
    }
    myLCD_BL=1.0f;
}

void Traffic_Lights(){
    while (true)
    {

        Pedestrian=0;

        Traffic_Lights_1 = RED;
        Traffic_Lights_2 = 3;//7-GREEN;
        ThisThread::sleep_for(DELAY);

        Pedestrian = 1;
        Traffic_Lights_1 = RED + AMBER;
        Traffic_Lights_2 = 5;//7-AMBER;
        ThisThread::sleep_for(DELAY);
        Traffic_Lights_1 = GREEN;
        Traffic_Lights_2 = 6;
        ThisThread::sleep_for(DELAY);
        Traffic_Lights_1 = AMBER;
        Traffic_Lights_2 = 4;
        ThisThread::sleep_for(DELAY);
    }
}

void Bar_Flash() {

//RGBled is the value of the Leds NB SHared Bus for Red Green and Blue
//RGBcol will select the Capitalised Colour NB rgb lower case is all off
// So Value then Latch and then latch off in that order
    while(true){
        RGBoe = 0; //Enable Output

        //RED
        RGBled = 255; RGBcol = Rgb; RGBcol = rgb; //NB see above i.e. LED value then latch High and Latch Low and repeat for below
        ThisThread::sleep_for(DELAY/4);
        RGBled = 0; RGBcol = Rgb; RGBcol = rgb; 

        //GREEN
        RGBled = 255; RGBcol = rGb; RGBcol = rgb; 
        ThisThread::sleep_for(DELAY/4);
        RGBled = 0; RGBcol = rGb; RGBcol = rgb; 

        //BLUE
        RGBled = 255; RGBcol = rgB; RGBcol = rgb; 
        ThisThread::sleep_for(DELAY/4);
        RGBled = 0; RGBcol = rgB; RGBcol = rgb; 

        // Put all LEDs on
        RGBled = 255; RGBcol = Rgb; RGBcol = rgb; 
        RGBled = 255; RGBcol = rGb; RGBcol = rgb; 
        RGBled = 255; RGBcol = rgB; RGBcol = rgb; 
        //Use Output Enable line to flash LED bar    
        for(int i=0; i<20;i++){
            RGBoe = !RGBoe;
            ThisThread::sleep_for(100ms);
        }
        // Reset Red Green and Blue to Zero and latch
        RGBled = 0; RGBcol = Rgb; RGBcol = rgb; 
        RGBled = 0; RGBcol = rGb; RGBcol = rgb; 
        RGBled = 0; RGBcol = rgB; RGBcol = rgb; 

        RGBoe = 1;//Disable Output
    }

}

const unsigned char test[] = {
    0xFF,0x18,0x18,0x18,0x18,0x18,0x18,0xFF
};

void writeSPI() {

}

float getLargest (float values[]) {
    float largest=0;
    float smallest=0;
    int arraySize = sizeof(values)/sizeof(values[0]);
    for (int i=0; i<arraySize; i++) {
        if (values[i]>largest) {
            largest=values[i];
        }
    } 

    return largest;
}

/*
float* quantise (float values[]) {
    //float scale = largest/8;
    float scale=0;
    float largest=0;
    int arraySize=sizeof(values)/sizeof(values[0]);
    float averaged_values[(arraySize/2)]; 

    // average samples, reducing sample from 32 results to 16
    for (int i=0; i<arraySize/2; i+=2) {
        averaged_values[i] = (values[i] + values[i+1])/2;
    };

    // get largest value from avereaged values
    for (int i=0; i<arraySize/2; i++) {
        if (values[i]>largest) {
            largest=values[i];
        }
    } 

    scale = largest/8;

    // quantise results using newly claculated scale
    for (int i=0; i<arraySize/2; i++) {
        averaged_values[i]=round(averaged_values[i] / scale) * scale;
    }

    // return quantised results
    return values;
}*/

/*
void quantise () {
    float values[] = {0.483873, 1.625253, 0.839204, 0.869297, 0.897305, 1.004262, 0.623505, 0.480197, 1.089175, 0.653027, 0.929283, 0.618130, 0.577199, 0.606022, 0.773732, 0.874227, 0.588949, 0.805187, 0.714122, 0.701207, 0.589595, 0.691449, 0.514599, 0.679395, 0.756901, 0.468627, 0.786273, 0.596040, 0.736816, 0.432151, 0.389424, 0.234184};
    
    float scale=0.0;
    float largest=0.0;
    int row=0;
    int arraySize=sizeof(values)/sizeof(values[0]);
    float averaged_values[(arraySize/2)]; 

    // average samples, reducing sample from 32 results to 16
    
    volatile int j = 0;
    
    for (int i=0; i<arraySize/2; i++) {
        averaged_values[i] = (values[j] + values[j+1])/2;
        //cout << averaged_values[i] << " = " << values[j] << " + " << values[j+1] << endl;
        j+=2;
        //cout << averaged_values[i] << endl;
    };

    // get largest value from avereaged values
    for (int i=0; i<arraySize/2; i++) {
        if (averaged_values[i]>largest) {
            largest=averaged_values[i];
            //cout << "New largest: " << largest << endl;
        }
    } 


    scale = largest/8.0;
    //cout << "Scale: " << scale << endl;;

    // quantise results using newly claculated scale
    for (int i=0; i<arraySize/2; i++) {
        averaged_values[i]=round(averaged_values[i] / scale) * scale;
        //cout << averaged_values[i] << endl;
    }
    
    struct matrix_metadata{ 
        int row;
        int col;
    };   
    
    matrix_metadata led_matrix_data[arraySize/2];
    
    for (int i=0; i<arraySize/2; i++) {
        row = (int)((averaged_values[i]/largest)*8);
        led_matrix_data[i].row = row;
        led_matrix_data[i].col = i;
        
        //cout << "row " << led_matrix_data[i].row << " | col: " << led_matrix_data[i].col << endl;
    }




    // return quantised results
    //return values;
}
*/

/*
void testSPI(int nums[2]) {
    for (int i=0; i<8; i++) {
        cs=0;
        spi.write(nums[0]);
        spi.write(nums[1]);
        spi.write(i);
        cs=1;        
    }
}
*/


void quantise (float values[]) {
    //values = {0.483873, 1.625253, 0.839204, 0.869297, 0.897305, 1.004262, 0.623505, 0.480197, 1.089175, 0.653027, 0.929283, 0.618130, 0.577199, 0.606022, 0.773732, 0.874227, 0.588949, 0.805187, 0.714122, 0.701207, 0.589595, 0.691449, 0.514599, 0.679395, 0.756901, 0.468627, 0.786273, 0.596040, 0.736816, 0.432151, 0.389424, 0.234184};
    
    for (int i=0; i<32; i++) {
        printf("%f\n", values[i]);
    }

    float scale=0.0;
    float largest=0.0;
    int row=0;
    //int arraySize=sizeof(values)/sizeof(values[0]);
    int arraySize=32;
    int counter=arraySize/2;

    //printf("%d", counter);

    float averaged_values[counter]; 

    // average samples, reducing sample from 32 results to 16
    
    volatile int j = 0;
    
    //printf("PRINT ME");

    for (int i=0; i<counter; i++) {
        averaged_values[i] = (values[j] + values[j+1])/2;
        //cout << averaged_values[i] << " = " << values[j] << " + " << values[j+1] << endl;
        //printf("%f = %f + %f\n", averaged_values[i], values[j], values[j+1]);
        j+=2;
        //cout << averaged_values[i] << endl;
    };

    // get largest value from avereaged values
    for (int i=0; i<counter; i++) {
        if (averaged_values[i]>largest) {
            largest=averaged_values[i];
            //cout << "New largest: " << largest << endl;
        }
    } 

    scale = largest/8.0;
    //cout << "Scale: " << scale << endl;
    //printf("scale: %f", scale);


    //quantise results using newly claculated scale
    for (int i=0; i<counter; i++) {
        averaged_values[i]=round(averaged_values[i] / scale) * scale;
        //cout << averaged_values[i] << endl;
    }
    
    struct matrix_metadata{ 
        int row;
        int col;
    };   
    
    matrix_metadata led_matrix_data[counter];
    
//<counter

    for (int i=0; i<24; i++) {
        //printf("foor loop entered\n");
        row = (int)((averaged_values[i]/largest)*8);
        led_matrix_data[i].row = row;
        led_matrix_data[i].col = i;
        
        //cout << "row " << led_matrix_data[i].row << " | col: " << led_matrix_data[i].col << endl;

        //printf("row: %i | col: %i\n", led_matrix_data[i].row, led_matrix_data[i].col);
    }

    // return quantised results
    //return values;
    
    //cout << endl;
    
    int matrix_array[8][16]={0};
    
    //printf("matrix array part\n");

    int matrixledsize=sizeof(led_matrix_data)/sizeof(led_matrix_data[0]);
    //printf("size: %d\n", matrixledsize);

    for (int j=0; j<16; j++) {
            for (int i=0; i<led_matrix_data[j].row; i++) {
               matrix_array[i][j] = 1; 
               //printf("data: %d ", led_matrix_data[j].row);
               //printf("i: %i j: %i\n", i, j); 
            }
    }
    
    uint8_t result=0;
    
    int decimal = 0;
    int decimal2 = 0;
    
    int led_values_lhs[8]={0};
    int led_values_rhs[8]={0};
    
    //printf("decimal part starting ...\n");

    matrixData matrixValues; 

    for (int j=0; j<8; j++) {
        for (int i=7; i>=0; i--) {
            //cout << matrix_array[7][i];
            //result |= matrix_array[7][i] << (8-i);
            //printf("%x", result);
            decimal = decimal << 1 | matrix_array[j][i];
        }
        //cout << decimal << ", ";
        led_values_lhs[j]=decimal;
        matrixValues.leftSide[j]=decimal;
        //printf("lhs: %d\n", led_values_lhs[j]);
        decimal=0;
    }

    //printf("lhs done ...\n");
    
    //cout << endl;
    //cout << endl;
    
    
    for (int j=0; j<8; j++) {
        for (int i=15; i>=8; i--) {
            //cout << matrix_array[7][i];
            //result |= matrix_array[7][i] << (8-i);
            //printf("%x", result);
            decimal2 = decimal2 << 1 | matrix_array[j][i];
        }
        //cout << decimal2 << ",";
        led_values_rhs[j]=decimal2;
        matrixValues.rightSide[j]=decimal2;
        //printf("rhs: %d\n", led_values_rhs[j]);
        decimal2=0;
    }

    t5Queue.call_every(15ms, writeMatrix, matrixValues);


    //printf("rhs done ...\n");
    
    //printf("Getting ready to write values...\n");

    //cout << endl;
    //cout << endl;

    // To-do: 
    // -> connect to DFT output 
    // -> convert to a class

    //printf("writing\n");

    
/*
    while (true) {
        for (int i=0; i<8; i++) {
            cs=0;
            //int rhs=led_values_rhs[i];
            //int lhs=led_values_lhs[i];
            //int s_row=i;
            spi.write(led_values_rhs[i]);
            spi.write(led_values_lhs[i]);
            spi.write(i);
            //printf("%d\n", led_values_rhs[i]);
            //printf("%d\n", led_values_lhs[i]);
            //printf("%d\n", i);
            //printf("%d\n", led_values_rhs[i]);
            //printf("%d\n", led_values_lhs[i]);
            //printf("%d\n", i);
            //printf("\n");

            //spi.write(255);
            //spi.write(7);
            //spi.write(i);
            //printf("%d\n",i);
            cs=1;        
        }
    }
    */

}




/*
int main() {
    /*
    float sample[] = {0.483873, 1.625253, 0.839204, 0.869297, 0.897305, 1.004262, 0.623505, 0.480197, 1.089175, 0.653027, 0.929283, 0.618130, 0.577199, 0.606022, 0.773732, 0.874227, 0.588949, 0.805187, 0.714122, 0.701207, 0.589595, 0.691449, 0.514599, 0.679395, 0.756901, 0.468627, 0.786273, 0.596040, 0.736816};
    
    int sampleArraySize = sizeof(sample)/sizeof(sample[0]);
    
    float quantised[sampleArraySize] = quantise(sample);
    */
    /*
    
    quantise();

    return 0;
}
*/

void illuminate (float values[], float largest) {
    bool time_up=false;
    float scale = largest/8;
    int arraySize = sizeof(values)/sizeof(values[0]);

    for (int i=0; i<arraySize; i++) {
        int mag = values[i]/scale;
        for (int j=0; j<8; j++) {
            
        }

        stopwatch.start();
        while (!time_up) {
            



            if (duration_cast<std::chrono::milliseconds>(stopwatch.elapsed_time()).count() > 2000) {
                time_up=true;
            }
        }
    }
    
}


void matrix_bars() {
    while(true) {
        
            cs=0;
            spi.write(7);
            spi.write(0);
            spi.write(1);
            cs=1;


        //for (int i=1; i<9; i++) {
            
            /*
            cs=0; 
            spi.write(0xFF);  //COL RHS
            spi.write(0x00);   //COL LHS
            spi.write(0);   //ROW RHS
            //spi.write(1);   //ROW RHS
            cs=1;

            cs=0; 
            spi.write(0x7C);  //COL RHS
            spi.write(0x00);   //COL LHS
            spi.write(1);   //ROW RHS
            cs=1; 

            cs=0; 
            spi.write(0x78);  //COL RHS
            spi.write(0x00);   //COL LHS
            spi.write(2);   //ROW RHS
            cs=1; 

            cs=0; 
            spi.write(0x38);  //COL RHS
            spi.write(0x00);   //COL LHS
            spi.write(3);   //ROW RHS
            cs=1; 

            cs=0; 
            spi.write(0x30);  //COL RHS
            spi.write(0x00);   //COL LHS
            spi.write(4);   //ROW RHS
            cs=1; 

            cs=0; 
            spi.write(0x10);  //COL RHS
            spi.write(0x00);   //COL LHS
            spi.write(5);   //ROW RHS
            cs=1; 

            cs=0; 
            spi.write(0x10);  //COL RHS
            spi.write(0x00);   //COL LHS
            spi.write(6);   //ROW RHS
            cs=1; 
            
            cs=0; 
            spi.write(0x3E);  //COL RHS
            spi.write(0x00);   //COL LHS
            spi.write(6);   //ROW RHS
            cs=1; 
            */
        //}
              //Send Data to Matrix
        //thread_sleep_for(1000);
    }
}

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

void count_thread(){
    seg7clear();
    unsigned char counter=0;
    while(true){
        seg7num(counter);
        counter++;
        if (counter>99){counter=0;}
        thread_sleep_for(250);
    }
}


int seg7num(int num){
    int temp,count=0;

    if (num<0||num>99){return -1;} // Out of Range check

    while(count<2){
        if (count==0){temp=(num/10)%10;} // Tens
        if (count==1){temp=num%10;}      // Units
        switch(temp){
            case 0: seg7=A+B+C+D+E+F;break;
            case 1: seg7=B+C;break;
            case 2: seg7=A+B+D+E+G;break;
            case 3: seg7=A+B+C+D+G;break;
            case 4: seg7=B+C+F+G;break;
            case 5: seg7=A+C+D+F+G;break;
            case 6: seg7=C+D+E+F+G;break;
            case 7: seg7=A+B+C;break;
            case 8: seg7=A+B+C+D+E+F+G;break;
            case 9: seg7=A+B+C+D+F+G;break;
            default: seg7=0;break;
        }
        if (count==0){LatE1=1;LatE1=0;} //Latch Tens Digit
        if (count==1){LatE2=1;LatE2=0;} //Latch Units Digit
        count++;
    }
    return 0; // Return Completed OK
}


void seg7clear(void){
    seg7=0;
    LatE1=1;LatE1=0;
    LatE2=1;LatE2=0;
}
 
void environment_data(void)
{   int err=0;
    float temperature,pressure;
    
    err = sensor.initialize();
    DEBUG_PRINT("ERROR CODE IS %d\n",err);
    switch (err){
        case 280: sensor.~SPL06_001_SPI(); bmp280.initialize();printf("BMP280 found\n");break;      //BMP280 found so Destruct SPL06 driver and initialize BMP280 !!
        case   6: bmp280.~BMP280_SPI();sensor.initialize();printf("SPL06_001 found\n");break;                           //SPL06_001 found so Destruct BMP280
        case  -1: printf("No Environmental Sensor found!\n");break;            //None found
        default : break;                                 
    }

    while(true)
    {
        switch (err)
        {
            case 280:temperature=bmp280.getTemperature();pressure=bmp280.getPressure();break;
            case 6:temperature=sensor.getTemperature();pressure=sensor.getPressure();break;
            case -1:break;
            default:break;
        }

        printf("Temperature = %4.1f ",temperature);
        printf("Pressure = %4.1f\n",pressure);
        thread_sleep_for(WAIT_TIME_MS);
    }
}

int write_sdcard()
{
    printf("Initialise and write to a file\n");
 int err;
    // call the SDBlockDevice instance initialisation method.

    err=sd.init();
    if ( 0 != err) {
        printf("Init failed %d\n",err);
        return -1;
    }
    
    FATFileSystem fs("sd", &sd);
    FILE *fp = fopen("/sd/test.txt","w");
    if(fp == NULL) {
        error("Could not open file for write\n");
        sd.deinit();
        return -1;
    } else {
        //Put some text in the file...
        fprintf(fp, "Martin Says Hi!\n");
        //Tidy up here
        fclose(fp);
        printf("SD Write done...\n");
        sd.deinit();
        return 0;
    }
    
}

int read_sdcard()
{
    printf("Initialise and read from a file\n");

    // call the SDBlockDevice instance initialisation method.
    if ( 0 != sd.init()) {
        printf("Init failed \n");
        return -1;
    }
    
    FATFileSystem fs("sd", &sd);
    FILE *fp = fopen("/sd/test.txt","r");
    if(fp == NULL) {
        error("Could not open or find file for read\n");
        sd.deinit();
        return -1;
    } else {
        //Put some text in the file...
        char buff[64]; buff[63] = 0;
        while (!feof(fp)) {
            fgets(buff, 63, fp);
            printf("%s\n", buff);
        }
        //Tidy up here
        fclose(fp);
        printf("SD Write done...\n");
        sd.deinit();
        return 0;
    }
}