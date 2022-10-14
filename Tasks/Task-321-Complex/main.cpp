#include "mbed.h"
#include "ComplexNumber.hpp"

// main() runs in its own thread in the OS
int main()
{
    
    //cls();
    printf("********* STARTING NEW ***********");
    ComplexNumber c1(2.0,3.0);
    ComplexNumber c2(1.0,-1.0);
    ComplexNumber c1_copy = c1;
    
    c1.add(c2);   //c1 = c1 + c2
    printf("c1 value:");
    c1.display();
    printf("c1_copy value:");
    c1_copy.display();
    
    printf("c1 value:");
    c1.display();
    printf("c2 value:");
    c2.display();

    ComplexNumber c3 = c1.addedTo(c2);
    printf("c3 value:");
    c3.display();
    c3.conjugate();
    printf("c3 conjugate:");
    c3.display();


    ComplexNumber c4 = c3.negated();
    printf("c3 negated (stored copy is c4): ");
    c4.display();

    c3.negate();
    printf("c3 negate: ");
    c3.display();

    c3.subtract(c1_copy);
    printf("c3-(2+3j): ");
    c3.display();


    ComplexNumber c5 = c3.subtractFrom(c1_copy);
    printf("c1_copy: ");
    c1_copy.display();

    printf("c1_copy subtracted from c3: ");
    c3.display();
    c5.display();

    printf("c3: ");
    c3.display();
    c3.multiply(5);
    printf("c3 * 5: ");
    c3.display();


    printf("\n***c3: ");
    c3.display();
    printf("\n***c1: ");
    c1.display();
    

    ComplexNumber a(1.0, 2.0);
    ComplexNumber b(-3.0, 1.0);
    a.display();
    b.display();
    a.multiplyWith(b);
    a.display();

    
    printf("c3 * c1: ");
    c3.display();

    c3.divide(2);
    printf("c3/2: ");
    c3.display();

    c3.divideWith(c1);
    printf("c3/c1: ");
    c3.display();

    //DONE!!!


    //Create new scope
    {
        ComplexNumber test(1.0);
        test.display();
    }
    //test is now out of scope and should be destroyed

    while (true);
    
}

