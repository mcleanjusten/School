// NAME: Justen McLean
// CLASS: Data Structures TTH 6:30pm 
// ASSIGNMENT: HW 2 Problem 3
// FILE: complexnum.h
// CLASS PROVIDED: complexnum
//
//      This class implements a few of the possible operators that could be used on complex numbers, it can add, subtract,
//  multiply and compare complex numbers by overriding the appropriate opperator operators and returning the appropiate data.
//  It would also be possible to add other operations such as division but was not done here because of the complexity 
//  associated with the implementation.
//
// CONSTRUCTORS for the throttle class:
//  complexnum(double rNum, double iNum);
//     Precondition: rNum and iNum must be valid doubles
//     Postcondition: rPart should be set to rNum and iPart should be set to iNum
//
// CONSTANT MEMBER FUNCTIONS for the banker class:
//   double getR() const {return rPart;}
//     Postcondition: Return the value of the real part of the complex number
//   double getI() const {return iPart;}
//     Postcondition: Return the value of the imaginary part of the complex number
// OVERRIDDEN OPERATORS
//   complexnum operator + (const complexnum& c1, const complexnum& c2)
//     Precondition: c1 and c2 must be pointers to complexnums
//     Postcondition: return a pointer to a new complex number with the sum of the real and imaginary parts
//   complexnum operator - (const complexnum& c1, const complexnum& c2);
//     Precondition: c1 and c2 must be pointers to complexnums
//     Postcondition: return a pointer to a new complex number with the difference of the real and imaginary parts
//   complexnum operator * (const complexnum& c1, const complexnum& c2);
//     Precondition: c1 and c2 must be pointers to complexnums
//     Postcondition: return a pointer to a new complex number with the product of the real and imaginary parts
//   double operator == (const complexnum& c1, const complexnum& c2);
//     Precondition: c1 and c2 must be pointers to complexnums
//     Postcondition: return a bool that is true if the complex numbers real and imaginary parts are equal

#ifndef COMPLEXNUM_H
#define COMPLEXNUM_H

namespace mclean_h2
{

class complexnum
{
public:
    complexnum(double rNum, double iNum);
    

    //Constant functions
    double getR() const {return rPart;}
    double getI() const {return iPart;}
    

private:
    double rPart;
    double iPart;
};

//Basic math operators are being overloaded
complexnum operator + (const complexnum& c1, const complexnum& c2);
complexnum operator - (const complexnum& c1, const complexnum& c2);
complexnum operator * (const complexnum& c1, const complexnum& c2);
double operator == (const complexnum& c1, const complexnum& c2);



}

#endif // COMPLEXNUM_H
