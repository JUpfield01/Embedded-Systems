//
//  ComplexNumber.hpp
//  Complex
//
//  Created by Nicholas Outram on 21/09/2017.
//  Copyright © 2017 Nicholas Outram. All rights reserved.
//

#ifndef ComplexNumber_hpp
#define ComplexNumber_hpp

#include "mbed.h"
#include <stdio.h>
#include <math.h>
#include <iostream>
using namespace std;

class ComplexNumber {
private:
    double real;
    double imag;
    
public:
    //Default constructor
    ComplexNumber() {
        this->real = 0.0;
        this->imag = 0.0;
    }
    
    //Constructor 2 - default of second parameter is 1 if not specified
    ComplexNumber(const double r, const double i=0.0) {
        this->real = r;
        this->imag = i;
    }
    
    
    //Copy constructors
    ComplexNumber(const ComplexNumber& c) {
        this->imag = c.imag;
        this->real = c.real;
    }
    

    //Destructor
    ~ComplexNumber() {
    }
    
    //Read-only accessors
    double getReal() {
        return this->real;
    }

    double getImag() {
        return this->imag;
    }

    //Conjugate - verb, so perform in place
    void conjugate() {
        this->imag *= -1.0;
    }
    
    //Conjugated - adjective, so return new copy
    ComplexNumber conjugated() {
        return ComplexNumber(this->real, -1.0*this->imag);
    }

    //Add in place
    void add(const ComplexNumber& c) {
        this->real += c.real;
        this->imag += c.imag;
    }
    
    //Subtract in place
    void subtract(const ComplexNumber& c) {
        this->real =real-c.real;
        this->imag =imag-c.imag;
    }
    
    //Subtract from
    ComplexNumber subtractFrom(const ComplexNumber& c) { 
        return ComplexNumber(this->real-c.real, this->imag-c.imag);   
    }
    
    //Add to
    ComplexNumber addedTo(const ComplexNumber& c) {
        return ComplexNumber(this->real+c.real, this->imag+c.imag);
    }

    //Negate in place
    void negate() {
        this->real = -real;
        this->imag = -imag;
    }
    
    //Negate and return copy
    ComplexNumber negated() {
        ComplexNumber c;
        c.real = -this->real;
        c.imag = -this->imag;
        return c;
    }
   
    //-----------| RERQUIRES ERROR CHECKING |-----------//
    
    //Multiply by a double
    void multiply(double multiplier) {
        this->real = this->real*multiplier;
        this->imag = this->imag*multiplier;
    }
    
    //Multiply two complex numbers ---| RERQUIRES ERROR CHECKING |---
    void multiplyWith(const ComplexNumber& c) {
        ComplexNumber temp(this->real,this->imag);

        this->real = ((temp.real*c.real)-(temp.imag*c.imag));
        this->imag = ((temp.real*c.imag)+(temp.imag*c.real));
    }
    
    void divide(double quotient) {
        this->real = real/quotient;
        this->imag = imag/quotient;
    }
    
    void divideWith(const ComplexNumber& c) {
        ComplexNumber temp(this->real,this->imag);
        this->real = (((temp.real*c.real)+(temp.imag*c.imag))/((pow(c.real,2)+(pow(c.imag,2))))); //cba to write this->real
        this->imag = (((temp.imag*c.real)-(temp.real*c.imag))/((pow(c.real,2)+(pow(c.imag,2))))); //cba to write this->imag
    }

    
    //Display
    void display() {
        cout << this->real << " + " << this->imag << "j" << endl;
    }
    
};


#endif /* ComplexNumber_hpp */
