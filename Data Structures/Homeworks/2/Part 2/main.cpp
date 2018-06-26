// NAME: Justen McLean
// CLASS: Data Structures TTH 6:30pm 
// ASSIGNMENT: HW 2 Problem 2
// Consulation: http://stackoverflow.com/questions/9138790/cant-use-modulus-on-doubles,
// http://en.cppreference.com/w/cpp/numeric/math/fmod - used to find the modulus of years and 1
#include <stdio.h>
#include <iostream>     //Allows for insteraction with the console
#include <banker.h>     //Allows access to the banker functions
#include <cmath>        //Allows access to the fmod function

using namespace std;            //Allow the use of standard functions
using namespace mclean_h2;      //Allow the use of banker functinos

int main(int argc, char **argv)
{
    //Variables
    double bal;                 //Account balance
    double intR;                //Interest rate
    double finalBal;            //The wanted final account balance
    double deposits;            //The amount of any yearly deposits
    double modYears;            //years % 1, used to check if a deposit needs to be added to the account
    double years = 0;           //Years or/and fractional years to get to desired account balance.
    
    
    
	//Program title
    cout<<"Bank Calculator"<<endl;
    cout<<"Find out how long an it will take to get a desired account balance at a your prefered interest rate"<<endl;
    
    //Prompt user
    cout<<"Enter an amount for the account balance: "<<endl;
    //Get Input
    cin>>bal;
    
    //Prompt user
    cout<<"Enter an amount for the interest rate: "<<endl;
    //Get Input
    cin>>intR;
    
    //Prompt user
    cout<<"Enter an amount for the final account: "<<endl;
    //Get Input
    cin>>finalBal;
    
        //Prompt user
    cout<<"Input the ammount of any yearly deposits, otherwise input 0 "<<endl;
    //Get Input
    cin>>deposits;
    
    
    //Create a new banker class instance with bal and intR
    banker account(bal,intR);
    
    
    //Add interest to the account at a .1 year until the balance >= the final balance
    while(account.getBalance() < finalBal){
        years = years + .1;     //Increment the year count
        modYears = fmod(years,1);
        if(modYears == 0){    //Check if a deposit needs to be added
            account.deposit(deposits);
        }
        account.addInterest(.1);    //Add interest

    }
    
    //Print the ammount of time it took in years and the final account balance
    cout<<"It took "<<years<<" years to get to a final account balance of "<<account.getBalance()<<endl;
    
    
    
    
    
    
    
	return 0;
}
