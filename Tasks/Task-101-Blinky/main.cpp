#include "mbed.h"
#include <iostream>

using namespace std;

struct matrixData {
    int leftValues[8]={0};
    int rightValues[8]={0};
};

void nest2(matrixData &test_) {
    printf("%d %d\n", test_.leftValues[1], test_.leftValues[2]);
    printf("%p\n", (void *)&test_);
};

void nest1(matrixData &test_) {
    test_.leftValues[2]=10;
    printf("%p\n", (void *)&test_);
    nest2(test_);
};


int main() {
    matrixData test;
    printf("%p\n", (void *)&test);
    
    test.leftValues[1] = 5;
    
    //cout << "Created  new matrixData" << endl;
    
    nest1(test);
    
    printf("%d %d\n", test.leftValues[1], test.leftValues[2]);

    return 0;
}