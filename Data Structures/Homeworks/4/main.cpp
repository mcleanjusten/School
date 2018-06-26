//Name: Justen McLean
//ASSIGNMENT: HOMEWORK 4
//FILE: mian.cpp


#include <stdio.h>
#include "poly0.h"



using namespace std;
using namespace main_savitch_3;

int main(int argc, char **argv)
{
	polynomial new_poly;
    
    new_poly.assign_coef(12,0);
    new_poly.assign_coef(5,1);
    new_poly.assign_coef(7,2);
    new_poly.assign_coef(8,3);
    new_poly.assign_coef(5,5);
    
    
    cout<<new_poly.coefficient(5)<<"X^5 + ";
    cout<<new_poly.coefficient(4)<<"X^4 + ";
    cout<<new_poly.coefficient(3)<<"X^3 + ";
    cout<<new_poly.coefficient(2)<<"X^2 + ";
    cout<<new_poly.coefficient(1)<<"X^1 + ";
    cout<<new_poly.coefficient(0)<<"X^0"<<endl;
    
	return 0;
}
