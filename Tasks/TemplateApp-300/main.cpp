#include "mbed.h"

#include<iostream>
#include<math.h>
using namespace std::chrono;
using namespace std;
#define PI 3.14159265

Timer tmr;

class DFT_Coeff {
   public:
   double real, img;
   DFT_Coeff() {
      real = 0.0;
      img = 0.0;
   }
};


int main() {
    int sampleSize=200;
    double function[sampleSize];
    for (int i = 0; i < sampleSize; i++) {
        function[i] = (0.01*(rand()%100));
    }
    int k = 0;
    for (; k<20; k++) {
        int n=0;
        int N=200;

        double cosine[sampleSize];
        double sine[sampleSize];

        for (; n<N-1; n++) {
            cosine[n] = cos((2 * n * k * PI) / sampleSize);
            sine[n] = sin((2 * n * k * PI) / sampleSize);
        }
        DFT_Coeff dft_value[k];
        
    }
}

int main(int argc, char **argv) {
   tmr.start(); 
   int M= 200;
   double function[M];
   for (int i = 0; i < M; i++) {
      function[i] = (0.01*(rand()%100));
      //System.out.print( " "+function[i] + " ");
   }
   //cout << "Enter the max K value: ";
   //int k=20; //Needs to go from 0 to 20
    for (int k=0; k<20; k++){
        double cosine[M];
        double sine[M];
    for (int i = 0; i < M; i++) {
        cosine[i] = cos((2 * i * k * PI) / M);
        sine[i] = sin((2 * i * k * PI) / M);
    }
    DFT_Coeff dft_value[k];
    //cout << "The coefficients are: ";
    for (int j = 0; j < k; j++) {
        for (int i = 0; i < M; i++) {
            dft_value[j].real += function[i] * cosine[i];
            dft_value[j].img += function[i] * sine[i];
        }
    }
        tmr.stop();
        printf("The time taken was %llu milliseconds\n", duration_cast<milliseconds>(tmr.elapsed_time()).count());
        for (int j = 0; j < k; j++) {
        for (int i = 0; i < M; i++) {
            cout << "(" << dft_value[j].real << ") - " << "(" << dft_value[j].img <<" i)";
        }
        } 
        
   }
   
}

