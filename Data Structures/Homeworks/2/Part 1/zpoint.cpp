// NAME: Justen McLean
// CLASS: Data Structures TTH 6:30pm 
// ASSIGNMENT: HW 2
#include "zpoint.h"
#include "cmath"    //provides access to sin and cos functions


using namespace mclean_h2;

    //Constructors
    zpoint::zpoint()        
    {
    }
    
    zpoint::zpoint(double newX, double newY, double newZ)        //Constructor that allows you to set the x,y,z coordinates on creation
    {
            x = newX;       //Set this instance of x to the value of newX
            y = newY;       //Set this instance of y to the value of newY
            z = newZ;       //Set this instnace of z to the value of newZ
    }
    
    //Member functions
    void zpoint::setLocation(double newX, double newY, double newZ)       //Moves a point to a new set of coordinates
    {
            x = newX;       //Set this instance of x to the value of newX
            y = newY;       //Set this instance of y to the value of newY
            z = newZ;       //Set this instnace of z to the value of newZ
    }
    
    void zpoint::shiftX(double amount)       //Moves a point along the x-axis
    {
            x = x+amount;
    }
    
    void zpoint::shiftY(double amount)       //Moves a point along the y-axis
    {
        y = y+amount;
    }
    
    void zpoint::shiftZ(double amount)       //Moves a point along the z-axis
    {
        z = z+amount;
    }
    
    void zpoint::rotateX(double angle)        //Rotates a point by the given angle amount around the x-axis
    {
        xPrime = x;
        yPrime = y * cos(angle) - z * sin(angle);
        zPrime = y * sin(angle) + z * cos(angle);
        
        //Set the point to the new coordinates currently held by the variables x',y',z'
        setLocation(xPrime, yPrime, zPrime);
    }
    
    void zpoint::rotateY(double angle)        //Rotates a point by the given angle amount around the y-axis
    {
        xPrime = x * cos(angle) - z * sin(angle);
        yPrime = y;
        zPrime = -x * sin(angle) + z * cos(angle);
        
        //Set the point to the new coordinates currently held by the variables x',y',z'
        setLocation(xPrime, yPrime, zPrime);
    }
    void zpoint::rotateZ(double angle)        //Rotates a point by the given angle amount around the z-axis
    {
        xPrime = x * cos(angle) - y * sin(angle);
        yPrime = x * sin(angle) + y * cos(angle);
        zPrime = z;
        
        //Set the point to the new coordinates currently held by the variables x',y',z'
        setLocation(xPrime, yPrime, zPrime);
        
    }
    
    
    
    



