//Name: Justen mclean
//Assignment: Homework 7
//Class: TTH 6:30 p.m.
//File: main.cpp
//About: Provides a function that compares too stacks to see if they are the same and returns a bool
//Testing: Testing of the function is provided in the main method
//

//Which of the three approaches (friend function, reference parameters, or value parameters)
//will be most efficient?
//
//I believe the most efficient approach would be to use a friend function and directly access the value of the stack in most cases.  
//This would allow you to avoid creating temporary stacks, then filling them, and then having to push the original numbers back to the 
//original stack.  




//bool compareStacks(stack<>& stackA,stack<>& stackB);
//Precondition: stackA and StackB must be int stacks
//Postcondition: compareStacks will compare each item in stackA to stackB if they differ at any point 
//false is returned
//




#include <stdio.h>          //Provides standard methods
#include <iostream>         //Provides cout and endl
#include <stack>            //Provides the stl stack

using namespace std;

//Compares two stacks and returns true if they are the same
bool compareStacks(stack<int>& stack_one, stack<int>& stack_two);

int main(int argc, char **argv)
{
    bool sameStack;
//Create three new stacks
    stack<int> stack_one;
    stack<int> stack_two;
    stack<int> stack_three;
    
//Stack ones values are: 9,3,2,1
    stack_one.push(1);
    stack_one.push(2);
    stack_one.push(3);
    stack_one.push(9);
    
//Stack twos values are: 9,4,2,1
    stack_two.push(1);
    stack_two.push(2);
    stack_two.push(4);
    stack_two.push(9);
    
//Stack threes values are: 9,3,2,1
    stack_three.push(1);
    stack_three.push(2);
    stack_three.push(3);
    stack_three.push(9);
    
    //Print the stack values
    cout<<"Stack ones values are: 9,3,2,1"<<endl;
    cout<<"Stack twos values are: 9,4,2,1"<<endl;
    cout<<"Stack threes values are: 9,3,2,1"<<endl;
    cout<<endl;
//Compare stack one and two and print if they are the same or not
    cout<<"Comparing stack one and stack two."<<endl;
    //Set sameStack to the return value of compareStacks
    sameStack = compareStacks(stack_one, stack_two);
    
    //Print the answer to the console
    if(sameStack){
        cout<<"The stacks are the same"<<endl;
    }
    else{
        cout<<"The stacks are not the same"<<endl;
    }
    cout<<endl;
//Compare stack one and three and print if they are the same or not
    cout<<"Comparing stack one and stack three."<<endl;
        //Set sameStack to the return value of compareStacks
    sameStack = compareStacks(stack_one, stack_three);
    
    //Print the answer to the console
    if(sameStack){
        cout<<"The stacks are the same"<<endl;
    }
    else{
        cout<<"The stacks are not the same"<<endl;
    }
    cout<<endl;
//Compare stacks two and three and print if they are the same or not
    cout<<"Comparing stack two and stack three."<<endl;
        //Set sameStack to the return value of compareStacks
    sameStack = compareStacks(stack_two, stack_three);
    
    //Print the answer to the console
    if(sameStack){
        cout<<"The stacks are the same"<<endl;
    }
    else{
        cout<<"The stacks are not the same"<<endl;
    }
    
	return 0;
}


//Compare 2 stacks and return true if they are the same
bool compareStacks(stack<int>& stack_one, stack<int>& stack_two){
    stack<int> stack_one_temp;          //Temporary stack to hold the numbers as they are popped out and checked
    stack<int> stack_two_temp;          //Temporary stack to hold the numbers as they are popped out and checked
    
    bool sameVals = true;               //Flag that is used to tell if the stacks are the same
    
    //Check that the stacks are the same size, if they are not then they are not the same
    if(stack_one.size() != stack_two.size())
        sameVals = false;
    
    //While loop to compare all the values in the stacks
    
    while(!stack_one.empty() && !stack_two.empty() && sameVals)
    {   
        //Push the first value in the stack to the temporary stacks
        stack_one_temp.push(stack_one.top());
        stack_two_temp.push(stack_two.top());
            
            //Check if the top values on each stack are the same
            if(stack_one.top() == stack_two.top()){
                stack_one.pop();        //remove the top value that has been copied to the temp stack
                stack_two.pop();        //remove the top value that has been copied to the temp stack
            }
            else{                       //The values are different so the stacks are not the same
                stack_one.pop();        //remove the top value that has been copied to the temp stack
                stack_two.pop();        //remove the top value that has been copied to the temp stack
                sameVals = false;       //Set the same vals flag as false so the while loop stops
            }

    }
    
    //All values of the stacks are now checked and the original stacks should be empty
    //Now cop all the original stack values from there temp stacks back to the original stack
    
    while(!stack_one_temp.empty() && !stack_two_temp.empty()){
        //Push top value to the original stacks
        stack_one.push(stack_one_temp.top());       //Push the top stack value of stack_one_temp to stack_one
        stack_two.push(stack_two_temp.top());       //Push the top stack value of stack_two_temp to stack_two
    
        //Pop top value from the temp stacks
        stack_one_temp.pop();
        stack_two_temp.pop();
    }

    return sameVals;
}

