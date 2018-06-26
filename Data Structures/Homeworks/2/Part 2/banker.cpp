// NAME: Justen McLean
// CLASS: Data Structures TTH 6:30pm 
// ASSIGNMENT: HW 2 Problem 2

#include "banker.h"
#include <assert.h>     //Gice access to assert.h

using namespace mclean_h2;


//Constructor
banker::banker()
{
    
}    
banker::banker(double initBal, double initInt)
{   
    assert(intRate<=0);       //
    balance = initBal;      //Set the balance to the initial balance
    intRate = initInt/100;      //Set the interest rate to the initial interest rate
}
    
//Member functions
void banker::setBalance(double newBal)
{
    balance = newBal;       //Set the balance equal to the newBal double
}

void banker::setIntRate(double newInt)
{
    intRate = (newInt / 100);   //Set the new interest rate
}

void banker::deposit(double amount)
{
    assert(amount >= 0);      //Check that the amount is greater than 0
    
    balance = balance + amount;     //Add the amount to the balance
}

void banker::withdrawl(double amount)
{
    assert(amount >= 0);       //Check that the amount is greater than 0

    balance = balance - amount;     //Subtract the amount from the balance
}

void banker::addInterest(double years)
{
    assert(years > 0 );                           //Check that years is valid
    double yearlyInt = intRate * balance;       //The amount of interest earned in year at the current rate
    double actualInt = yearlyInt * years;  //The actual amount of interest based on the number of years    
    balance = balance + actualInt;              //Add the interest to the account balance
}
    
