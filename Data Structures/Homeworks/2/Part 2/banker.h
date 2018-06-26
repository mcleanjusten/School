// NAME: Justen McLean
// CLASS: Data Structures TTH 6:30pm 
// ASSIGNMENT: HW 2 Problem 2
// FILE: banker.h
// CLASS PROVIDED: banker
//
// CONSTRUCTORS for the throttle class:
//   banker(double initBal, double initInt)
//     Precondition: initBal must be a double and initInt must be a double greater than 0
//     Postcondition: A new banker class instance is created with an initial balance and an initial interest set to the value provided in the function parameters
//
// MEMBER FUNCTIONS for the banker class:
//   void setBalance(double newBal);
//     Precondition: newBal must be a valid double value
//     Postcondition: the class balance variable must now be equal to newBal
//
//   void setIntRate(double newInt);
//     Precondition: newBal must be a valid double value greater than 0
//     Postcondition: the class intRate varaible must reflect newInt
//
//   void deposit(double amount);
//     Precondition:  Amount must be a valid positive double value or 0
//     Postcondition: Balance has had amount added to it
//   
//   void withdrawl(double amount);
//     Precondition:  Amount is a valid positive double value
//     Postcondition: Balance has had amount subtracted from it
//
//   void addInterest(double years);
//     Precondition:  Years must be a valid positive non-zero double value
//     Postcondition: The balance must have years * the current interest rate added too it
//
// CONSTANT MEMBER FUNCTIONS for the banker class:
//   double getBalance() const {return balance;}
//     Postcondition: The value returned is the current balance in the account.
//   double getIntRate() const {return balance;}
//     Postcondition: The value returned is the current interest rate for the account.


#ifndef BANKER_H
#define BANKER_H

namespace mclean_h2
{

class banker
{
public:
    banker();
    banker(double initBal, double initInt);
    
    //Member functions
    void setBalance(double newBal);
    void setIntRate(double newInt);
    void deposit(double amount);
    void withdrawl(double amount);
    void addInterest(double years);
    
    //Constant functrions
    double getBalance() const {return balance;}
    double getIntRate() const {return intRate;}
    
private:
    double balance = 0;
    double intRate = 0;
};

}

#endif // BANKER_H
