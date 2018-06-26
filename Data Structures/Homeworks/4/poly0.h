// FILE: poly0.h
// NAME: Justen mclean
// ASSIGNMENT: Homework 4
// FILE: poly0.h
// CLASS PROVIDED:
//   class polynomial (in the namespace main_savitch_3)
//     A polynomial has one variable x, real number coefficients, and
//     non-negative integer exponents. Such a polynomial can be viewed
//     as having the form:
//       A[n]*x^n + A[n-1]*x^(n-1) + ... A[2]*x^2 + A[1]*x + A[0]
//     where the A[n] are the real number coefficients and x^i represents
//     the variable x raised to the i power. The coefficient A[0] is
//     called the "constant" or "zeroth" term of the polynomial.
//   
//
// CONSTRUCTOR for the polynomial class
//   polynomial(double a0)
//     PRECONDITION: a0 is the coefficent of x^0.
//     POSTCONDITION: This polynomial has been create with all zero
//     coefficients, except for coefficient a0 which is in the first position in the array
//
//   polynomial(const polynomial& source)
//     PRECONDITION: source is a already created polynomial
//     POSTCONDITION: Creates a new polynomial that is a copy of the on in source
//
//    ~polynomial()
//     POSTCONDITION: The dynamic array has been deleted
//
// MODIFICATION MEMBER FUNCTIONS for the polynomial class
//   void add_to_coef(double amount, unsigned int exponent)
//     POSTCONDITION: Adds the given amount to the coefficient of the
//     specified exponent.
//
//   void assign_coef(double coefficient, unsigned int exponent)
//     POSTCONDITION: Sets the coefficient for the specified exponent.
//
//   void clear( )
//     POSTCONDITION: All coefficients of this polynomial are set to zero.
//
// CONSTANT MEMBER FUNCTIONS for the polynomial class
//   double coefficient(unsigned int exponent) const
//     POSTCONDITION: Returns coefficient at specified exponent of this
//     polynomial.
//
//   unsigned int degree( ) const
//     POSTCONDITION: The function returns the value of the largest exponent
//     with a non-zero coefficient.
//     If all coefficients are zero, then the function returns zero.
//
//   double eval(double x) const
//     POSTCONDITION: The return value is the value of this polynomial with the
//     given value for the variable x.
//
//   unsigned int next_term(unsigned int e) const
//     POSTCONDITION: The return value is the next exponent n which is LARGER
//     than e such that coefficient(n) != 0.
//     If there is no such term, then the return value is zero.
//
//   unsigned int previous_term(unsigned int e) const
//     POSTCONDITION: The return value is the next exponent n which is SMALLER
//     than e such that coefficient(n) != 0.
//     If there is no such term, then the return value is UINT_MAX
//     from <climits>.
//
// CONSTANT OPERATORS for the polynomial class
//   double operator( ) (double x) const
//     Same as the eval member function.
//
// NON-MEMBER BINARY OPERATORS for the polynomial Class
//   polynomial operator -(const polynomial& p1, const polynomial& p2)
//     POSTCONDITION: return-value is a polynomial with each coefficient
//     equal to the difference of the coefficients of p1 & p2 for any given
//     exponent.
//
//   polynomial operator +(const polynomial& p1, const polynomial& p2)
//     POSTCONDITION: return-value is a polynomial with each coefficient
//     equal to the sum of the coefficients of p1 & p2 for any given
//     exponent.
//
//   polynomial operator *(const polynomial& p1, const polynomial& p2)
//     PRECONDITION: p1.degree( ) + p2.degree( ) <= polynomial::MAX_EX.
//     POSTCONDITION: Each term of p1 has been multiplied by each term of p2,
//     and the answer is the sum of all these term-by-term products.
//     For example, if p1 is 2x^2 + 3x + 4 and p2 is 5x^2 - 1x + 7, then the
//     return value is 10x^4 + 13x^3 + 31x^2 + 17x + 28.
//
//

#ifndef POLY0_H
#define POLY0_H
#include <iostream>  // Provides ostream

// If your compiler does not support namespaces, then please delete the
// following line and the set of brackets that follow.
namespace main_savitch_3
{
    
    class polynomial
    {
    public:
	// CONSTANTS
	
	
	
    // CONSTRUCTOR
	polynomial();       //Defaul constructor
    polynomial(double a0);      //Sets the x^0 coefficent only
    polynomial(const polynomial& source);       //Copy constructor
    ~polynomial();

	// MODIFICATION MEMBER FUNCTIONS
	void add_to_coef(double amount, unsigned int exponent);
	void assign_coef(double coefficient, unsigned int exponent);
	void clear( );
    void reserve(size_t number);
	
	// CONSTANT MEMBER FUNCTIONS
	double coefficient(unsigned int exponent) const;
	unsigned int degree( ) const { return current_degree; }
	//polynomial derivative( ) const;
	double eval(double x) const;
	unsigned int next_term(unsigned int e) const;
	unsigned int previous_term(unsigned int e) const;
	
	// CONSTANT OPERATORS
	double operator( ) (double x) const { return eval(x); }
    
    //MEMBER OPERATORS
    polynomial& operator =(const polynomial& source){
    
    return *this;}
    polynomial& operator =(double a0);
    
    
    private:
    size_t size;
    double * poly_array;
	//double coef[size];
	unsigned int current_degree;

		void compute_degree();
    };
    
    // NON-MEMBER BINARY OPERATORS
    polynomial operator +(const polynomial& p1, const polynomial& p2);
    polynomial operator -(const polynomial& p1, const polynomial& p2);

    //polynomial operator *(const polynomial& p1, const polynomial& p2);
    
    // NON-MEMBER OUTPUT FUNCTIONS
    std::ostream& operator << (std::ostream& out, const polynomial& p);


}
#endif