#include "mbed.h"
#include "Complex_C.hpp"

// TASK - write and test complexConjugate, complexNegate, complexSubtract, complexMagnitude, complexMultiply and complexDivide

int main() {
    printf("\n\nTASK312\n");

    //Create instance of a complex number
    ComplexNumber_C p = {2.0, 3.0};
    ComplexNumber_C q = {1.0, 1.0};
    complexDisplay("p", p);
    complexDisplay("q", q);
 
    ComplexNumber_C sum = complexAdd(p, q);
    complexDisplay("p+q", sum);

    ComplexNumber_C conjugate = complexConjugate(p);
    complexDisplay("p conj", conjugate);

    ComplexNumber_C negate = complexNegate(p);
    complexDisplay("p neg", conjugate);

    ComplexNumber_C subtract = complexSubtract(p,q);
    complexDisplay("p-q", subtract);

    double magnitude = complexMagnitude(p);
    printf("p mag %f\n", magnitude);

    double magnitude2 = complexMagnitude(q);
    printf("q mag %f\n", magnitude2);

    ComplexNumber_C multiply = complexMultiply(p,q);
    complexDisplay("p*q", multiply);

    ComplexNumber_C divide = complexDivide(p,q);
    complexDisplay("p/q", divide);

    complexConjugateInplace(p);
    complexDisplay("CIP q:",p);
    
    complexConjugateInplace(q);
    complexDisplay("CIP q:",q);

    while (true) {
    }
}
