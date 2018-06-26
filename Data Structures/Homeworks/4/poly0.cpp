// FILE: poly0.h
// NAME: Justen mclean
// ASSIGNMENT: Homework 4
// CONSULTATOIN:  http://www.cplusplus.com/reference/cmath/pow/ - pow function

#include "poly0.h"
#include <iostream> //Provides cout
#include <assert.h> //Provides assert
#include "limits.h" //Provides UINT_MAX
#include <cmath>    //Provides cmath

using namespace main_savitch_3;
using namespace std;

// CONSTRUCTOR
polynomial::polynomial(){               //Gets the size from the user then points poly_array to a new double array of the user specified size
    
    //cout<<"What is the degree of the leading coefficent"<<endl;
    //cin>>size;      //Get the size from the user 
    
    poly_array = new double[1];        //creates a new double array with size = to the degree of the leading coefficent +1
    poly_array[0] = 0;      //Sets the x^0 value to 0
    current_degree = 0;         //Sets the current degree
        
}

polynomial::polynomial(double a0)      //Sets the x^0 coefficent only 
{
    cout<<"What is the degree of the leading coefficent"<<endl;
    cin>>size;      //Get the size from the user 
    
    poly_array = new double[size+1];        //creates a new double array with size = to the degree of the leading coefficent +1
    current_degree = 0;                     //Sets the current degree
    poly_array[0] = a0;
}

polynomial:: polynomial(const polynomial& source)       //Copy constructor
{
    poly_array = new double[source.size];
    current_degree = source.current_degree;
    size = source.size;
    
    //Copy all the values from the source
    for(int i = 0 ; i < size+1; i++){
        poly_array[i] = source.coefficient(i);
    }
    
}

polynomial::~polynomial(){
    delete[] poly_array;
}

// MODIFICATION MEMBER FUNCTIONS
void polynomial::add_to_coef(double amount, unsigned int exponent){
    poly_array[exponent] += amount;     //Set the value of the poly_array
}
void polynomial::assign_coef(double coefficient, unsigned int exponent){            //Creates a new coefficent
    //assert(exponent<=size);         //Check that the exponent value is valid
    if(exponent > (size+1))
    {
        polynomial::reserve(5);     //Increase the size of the array by 5

    }
    if(exponent > current_degree){      //Check if the current_degree needs to be changed to the value of this new coefficent
        current_degree = exponent;
    }
    
    poly_array[exponent] = coefficient;     //Set the value of the poly_array
}
void polynomial::clear( ){                  //Sets all the values of the array to 0 by linking to a new array of the same size
    double * old_poly_array = poly_array;
    poly_array = new double[size+1];
    delete[] old_poly_array;
}

void polynomial::reserve(size_t number)
{
    size += number;         //Increase the variable holding the size of arrray by amount number
    
    double * old_poly_array = poly_array;       //create a pointer to the old array
    poly_array = new double[size+1];            //point poly_array to  a new array
    
    for(int i = 0; i < size+1; i++)             //Copy the values from the original array
    {
            poly_array[i]= old_poly_array[i];       
    }
    delete[] old_poly_array;                    //Delete the pointer to the array
    
}

	
// CONSTANT MEMBER FUNCTIONS
double polynomial::coefficient(unsigned int exponent) const{
    return poly_array[exponent];
}

//polynomial derivative( ) const;
double polynomial::eval(double x) const {               //evaluates a polynomail for a given value of x
    double returnValue = poly_array[0];         //The value to return
    
    for(int i = size;i > 0; i--)      //For loop to perform the evalutation
    {
        returnValue += pow(x,i) * poly_array[i];
    }
    
    return returnValue;         //retrun the calculated value
    
}


unsigned int polynomial::next_term(unsigned int e) const {
    if(current_degree < size+1)         //Make sure it is in bounds
    {
            int i = current_degree+1;         //new iterator
            while( i <size+1){              //While loop to check all the positions after the current_degree for a non-zero coefficent
                if(poly_array[i]!= 0)
                    return poly_array[i];
                else 
                    i++;
            }
            
    }
    else
        return UINT_MAX;                    //Returned if there is not another term in the polynomial
;
}
unsigned int polynomial::previous_term(unsigned int e) const {
    if(current_degree > 0)         //Make sure it is in bounds
    {
            int i = current_degree+1;         //new iterator
            while( i <size+1){              //While loop to check all the positions after the current_degree for a non-zero coefficent
                if(poly_array[i]!= 0)
                    return poly_array[i];
                else 
                    i--;
            }
    }
    else
        return 0;
    
}
	
	

    
// NON-MEMBER BINARY OPERATORS
polynomial operator +(const polynomial& p1, const polynomial& p2)
{
    //Variables
    int p1Degree = p1.degree(); 
    int p2Degree = p2.degree();
    int degree;
    double sum;
    
    polynomial sum_poly;        //Create a new polynomial to hold the sum
    
    //Find the higher degree
    if(p1Degree >= p2Degree){
        degree = p1Degree;
    }
    else
    {
        degree = p2Degree;
    }
    
    // Add the values of the coefficients
    for(int i = 0; i < degree; i++)
    {
        sum = p1.coefficient(i)+p2.coefficient(i);      //Get the sumation of the two poly objects at exponent i
        sum_poly.assign_coef(sum,i);                    //Add the value to the new poly array
    }
    
    return sum_poly;
    
    
}
polynomial operator -(const polynomial& p1, const polynomial& p2)
{
    //Variables
    int p1Degree = p1.degree(); 
    int p2Degree = p2.degree();
    int degree;
    double diff;
    
    polynomial diff_poly;        //Create a new polynomial to hold the sum
    
    //Find the higher degree
    if(p1Degree >= p2Degree){
        degree = p1Degree;
    }
    else
    {
        degree = p2Degree;
    }
    
    // Add the values of the coefficients
    for(int i = 0; i < degree; i++)
    {
        diff = p1.coefficient(i)-p2.coefficient(i);      //Get the sumation of the two poly objects at exponent i
        diff_poly.assign_coef(diff,i);                    //Add the value to the new poly array
    }
    
    return diff_poly;
   
}

//polynomial operator *(const polynomial& p1, const polynomial& p2);
    
// NON-MEMBER OUTPUT FUNCTIONS
std::ostream& operator << (std::ostream& out, const polynomial& p);
