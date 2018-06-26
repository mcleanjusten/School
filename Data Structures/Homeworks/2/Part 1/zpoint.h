// NAME: Justen McLean
// CLASS: Data Structures TTH 6:30pm 
// ASSIGNMENT: HW 2 Problem 1
// FILE: zpoint.h
// CLASS PROVIDED: zpoint 
//
// CONSTRUCTORS for the throttle class:
//   zpoint( )
//     Postcondition: A new point is created with coordinates 0,0,0.
//
//   zpoint(double newX, double newY, double newZ)
//     Precondition:  newX, newY, newZ must all be valid double values
//     Postcondition: Point is created with the coordinates provided as the function arguement
//
// MEMBER FUNCTIONS for the zpoint class:
//
//   void setLocation(double newX, double newY, double newZ);
//     Precondition:  newX, newY, newZ must all be valid double values
//     Postcondition: Point is created with the coordinates provided as the function arguement
//   
//   void shiftX(double amount);
//     Precondition:  amount is a valid double value
//     Postcondition: x has been increased or decreased by amount as neccesarry
//
//   void shiftY(double amount);
//     Precondition:  amount is a valid double value
//     Postcondition: y has been increased or decreased by amount as neccesarry
//
//   void shiftZ(double amount);
//     Precondition:  amount is a valid double value
//     Postcondition: z has been increased or decreased by amount as neccesarry
//
//   void rotateX(double angle);
//     Precondition:  angle is a valid double value between 0 and 360
//     Postcondition: the point has been rotated around the x-axis and the new x,y,z values have been stored
//
//   void rotateY(double angle);
//     Precondition:  angle is a valid double value between 0 and 360
//     Postcondition: the point has been rotated around the y-axis and the new x,y,z values have been stored
//
//   void rotateZ(double angle);
//     Precondition:  angle is a valid double value between 0 and 360
//     Postcondition: the point has been rotated around the z-axis and the new x,y,z values have been stored
//
//
// CONSTANT MEMBER FUNCTIONS for the zpoint class:
//   double getX() const { return x;}
//     Postcondition: The value returned is the current x coordinate of type double.
//
//   double getY() const { return y;}
//     Postcondition: The value returned is the current y coordinate of type double.
//
//   double getZ() const { return z;}
//     Postcondition: The value returned is the current z coordinate of type double.


#ifndef ZPOINT_H
#define ZPOINT_H

namespace mclean_h2
{

class zpoint
{
public:
    //Variables for x,y,z prime values
    double xPrime;
    double yPrime;
    double zPrime;

    //Constructors
    zpoint();
    zpoint(double newX, double newY, double newZ);
    
    //Member functions
    void setLocation(double newX, double newY, double newZ);
    
    //Shift x,y,z
    void shiftX(double amount);
    void shiftY(double amount);
    void shiftZ(double amount);
    
    //Rotate x,y,z
    void rotateX(double angle);
    void rotateY(double angle);
    void rotateZ(double angle);
    
    // CONSTANT MEMBER FUNCTIONS
    double getX() const { return x;}
    double getY() const { return y;}
    double getZ() const { return z;}
    
    
private:
    //Variables for point coordinates
    double x = 0;
    double y = 0;
    double z = 0;
};

}

#endif // ZPOINT_H
