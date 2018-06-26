//Constultation: http://www.clarku.edu/~djoyce/complex/mult.html - used for learning how to multiply complex numbers

#include "complexnum.h"

using namespace mclean_h2;

//Constructor
complexnum::complexnum(double rNum, double iNum){
    rPart = rNum;
    iPart = iNum;
}

//Overloading operators

//Adding complex numbers
complexnum operator + (const complexnum& c1, const complexnum& c2)
{
    double rSum;
    double iSum;
    
    //Get the new real and imaginary sums
    rSum = c1.getR() + c2.getR();
    iSum = c1.getI() + c2.getI();
    
    //Create a new complexnum with the value of rSum and iSum
    complexnum complexSum(rSum,iSum);
    return complexSum;
    
}

//subtract complex numbers
complexnum operator - (const complexnum& c1, const complexnum& c2)
{
    double rDif;
    double iDif;
    
    //Get the new real and imaginary sums
    rDif = c1.getR() - c2.getR();
    iDif = c1.getI() - c2.getI();
    
    //Create a new complexnum with the value of rSum and iSum
    complexnum complexDif(rDif,iDif);
    return complexDif;
}

//Multiply complex numbers
complexnum operator * (const complexnum& c1, const complexnum& c2)
{
    double rProd;
    double iProd;
    
    //Get the new real and imaginary producs using the formula for multiplying complex numbers
    rProd = (c1.getR() * c2.getR()) - (c1.getI()*c2.getI());
    iProd = (c1.getR() * c2.getI()) + (c1.getR()*c2.getR());
    
    //Create a new complexnum with the value of rSum and iSum
    complexnum complexProd(rProd,iProd);
    return complexProd;
}

//Compare complex numbers
bool operator == (const complexnum& c1, const complexnum& c2){
    bool rCheck;
    bool iCheck;
    
    //Check if the real parts match and the imaginary parts match
    rBool = (c1.getR() == c2.getR());   //Compare real parts
    iBool = (c1.getI() == c2.getI());   //Compare imaginary parts
    
    if(rBool && iBool)      //If both the real and imaginary parts match return true
        return true;
        
    return false;
    
}

