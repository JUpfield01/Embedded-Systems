#include "stdio.h"
#include "math.h"
#include "Complex_C.hpp"

ComplexNumber_C complexAdd(const ComplexNumber_C a, const ComplexNumber_C b) {
    ComplexNumber_C y = a;
    y.real += b.real;
    y.imag += b.imag;
    return y;
}

ComplexNumber_C complexConjugate(const ComplexNumber_C a) {
    ComplexNumber_C y = {a.real, -a.imag};
    return y;
}

ComplexNumber_C complexNegate(const ComplexNumber_C a) {
    ComplexNumber_C y = {-a.real, -a.imag};
    return y;
}

ComplexNumber_C complexSubtract(const ComplexNumber_C a, const ComplexNumber_C b) {
    ComplexNumber_C y = complexNegate(b);
    ComplexNumber_C x = complexAdd(a,y);
    return x;
}

double complexMagnitude(const ComplexNumber_C a) {
    double real;
    double imag;
    double magnitude = sqrt(pow(a.real,2)+pow(a.imag,2));
    
    return magnitude;
}

ComplexNumber_C complexMultiply(const ComplexNumber_C a, const ComplexNumber_C b) {

    ComplexNumber_C y = {((a.real*b.real)-(a.imag*b.imag)),((a.real*b.imag)+(a.imag*b.real))};

    return y;
}

ComplexNumber_C complexDivide(const ComplexNumber_C a, const ComplexNumber_C b) {

    ComplexNumber_C y = {(((a.real*b.real)+(a.imag*b.imag))/((pow(b.real,2)+(pow(b.imag,2))))),(((a.imag*b.real)-(a.real*b.imag))/((pow(b.real,2)+(pow(b.imag,2)))))};

    return y;
}

void complexConjugateInplace(ComplexNumber_C& u) {
    u.imag = -u.imag;
}

void complexNegateInplace(ComplexNumber_C& u) {
    u.imag = -u.imag;
    u.real = -u.real;
}

void complexDisplay(const char *strName, const ComplexNumber_C u) {
    printf("%s = %f + j%f\n", strName, u.real, u.imag);
}