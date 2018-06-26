//Justen McLean
//1/14/2016
//CS 3304
//Homework 1 assignment 4
//Consultation:  http://stackoverflow.com/questions/5907031/printing-the-correct-number-of-decimal-points-with-cout 
//This program gets the number of burritos, salads, and milk shakes consumed and gives the number of calories and how many miles it would take to burn them off
#include <stdio.h>
#include <iostream>      //Used to get cin, cout
#include <iomanip>       //Used to help formatting
#include <assert.h>      //Used to get assert
using namespace std;

const int BEAN_BURRITO_CALORIES = 357;      //Number of calories in a bean burrito
const int SALAD_CALROIES = 185;             //Number of calories in a salad with dressing
const int MILK_SHAKE_CALORIES = 388;        //Number of calories in a milk shake
const int RUN_WALK_CALORIES = 100;          //Number of calories burned by running/walking a mile

int main(int argc, char **argv)
{
    //Variables
    double burritosConsumed;
    double saladsConsumed;
    double milkShakesConsumed;
    double totalCalories;
    double milesNeeded;
    
    //Get needed information from the user
	cout<<"How many bean burritos have you consumed?"<<endl;
    cin>>burritosConsumed;
    
    cout<<"How many bowls of salad have you consumed?"<<endl;
    cin>>saladsConsumed;
    
    cout<<"How many milk shakes have you consumed?"<<endl;
    cin>>milkShakesConsumed;
    
    //Get the total number of calories with the 
    totalCalories = (burritosConsumed*BEAN_BURRITO_CALORIES)+(saladsConsumed*SALAD_CALROIES)+(milkShakesConsumed*MILK_SHAKE_CALORIES);
    
    //output the total number of calories
    cout<<"You ingested "<<totalCalories<<" calories."<<endl;
    
    //Get the number of miles needed to burn that many calories
    milesNeeded = totalCalories/RUN_WALK_CALORIES;
    
    //output the number of miles needed 
    cout<<"You will have to run/walk "<< setprecision(2) << fixed << milesNeeded << " miles to expend that much energy."<<endl;
    
	return 0;
}
