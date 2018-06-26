// NAME: Justen McLean
// CLASS: Data Structures TTH 6:30pm 
// ASSIGNMENT: HW 2
// Citation: http://stackoverflow.com/questions/877523/error-request-for-member-in-which-is-of-non-class-type, used for help debugging
#include <stdio.h>
#include <zpoint.h>
#include <iostream>     //Allow printing to the console


using namespace std;
using namespace mclean_h2;

//Constants
//X,Y,Z new point location
double const XVAL = 5;
double const YVAL = 9;
double const ZVAL = 4;
//X,Y,Z amounts to shift by
double const XSHIFT = 1;
double const YSHIFT = 2;
double const ZSHIFT = -2;
//X,Y,Z amounts to rotate by in degrees
double const XROTATE = 45;
double const YROTATE = 30;
double const ZROTATE = 10;

int main(int argc, char **argv)
{
    //Create a new zpoint;
    zpoint newPoint;
    
    cout<<"Created a point with the coordinates: "<<endl;
    cout<< newPoint.getX()<<", "<<newPoint.getY()<<", "<<newPoint.getZ()<<endl;
    
    //Use the set location function to move the point 
    newPoint.setLocation(XVAL, YVAL, ZVAL);
    
    cout<<"Moved the point to the coordinates: "<<endl;
    cout<<newPoint.getX()<<", "<<newPoint.getY()<<", "<<newPoint.getZ()<<endl;
    
    
    
    
    //Use the shift functions to further move the point
    newPoint.shiftX(XSHIFT);
    
    cout<<"Shifted X by: "<<XSHIFT<<endl;
    cout<<newPoint.getX()<<", "<<newPoint.getY()<<", "<<newPoint.getZ()<<endl;
    
    newPoint.shiftY(YSHIFT);
    
    cout<<"Shifted Y by: "<<YSHIFT<<endl;
    cout<<newPoint.getX()<<", "<<newPoint.getY()<<", "<<newPoint.getZ()<<endl;
    
    newPoint.shiftZ(ZSHIFT);
    
    cout<<"Shifted Z by: "<<ZSHIFT<<endl;
    cout<<newPoint.getX()<<", "<<newPoint.getY()<<", "<<newPoint.getZ()<<endl;
    
    
    
    //Rotate the points
    newPoint.rotateX(XROTATE);
    
    cout<<"Rotated the point on the x-axis by: "<<XROTATE<<endl;
    cout<<newPoint.getX()<<", "<<newPoint.getY()<<", "<<newPoint.getZ()<<endl;
    
    newPoint.rotateY(YROTATE);
    
    cout<<"Rotated the point on the x-axis by: "<<XROTATE<<endl;
    cout<<newPoint.getX()<<", "<<newPoint.getY()<<", "<<newPoint.getZ()<<endl;    
    
    newPoint.rotateZ(ZROTATE);
    
    cout<<"Rotated the point on the x-axis by: "<<XROTATE<<endl;
    cout<<newPoint.getX()<<", "<<newPoint.getY()<<", "<<newPoint.getZ()<<endl;    
    
    
	return 0;
}
