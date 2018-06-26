//Name: Justen mclean
//Assignment: Homework 8
//Class: TTH 6:30 p.m.
//File: customer.cpp
//About: This class creates a new customer for the grocery simulation program
//
//void generateCustomers(int numToCreate);
//Precondition: numToCreate must be a positive integer and reflect the number of customers the simulation will run
//Postcondition: creates customers inside the globally accessible custArray
//
//void moveToCheckout(bool force);
//Precondition: force is false unless the function should force someone to checkout during that time period
//Postcondition: randomly selects a customer that has not previously checked out and sends them to the shortest line
//
//void simulate();
//Precondition: the curstArray must already by populated with customer objects
//Postcondition: the simulation must have run until there were no more customers left
//
//void sendToShortestLine(customer cust);
//Precondition: customer is a customer that has not been sent to a line yet and not null
//Postcondition: gets the shortest line and adds the customer too it, it also sets the customers wait clock so it starts counting
//it also make the person leave if the line is too long
//
//int getShortestLine();
//Postcondition: Compares the size() of the lines and gets the shortest one, it defaults to the earliest line in case of a tie
//
//void moveLine(customer cust, int line);
//void leaveStore();
//
//Postcondition: if a customer at the back of the line has exceeded the max wait time the must leave
//void checkOut();
//Postcondition: push customers out of check out if they have finished




//Includes
#include <stdio.h>
#include <iostream>
#include "customer.h"       //provides the customer class
#include <assert.h>
#include <deque>
using namespace std;
using namespace Mclean_Homework8;

//Method declarations
void generateCustomers(int numToCreate);
void moveToCheckout(bool force);
void simulate();
void sendToShortestLine(customer cust);
int getShortestLine();
void moveLine(customer cust, int line);
void leaveStore();
void printArray();
void checkOut();

//global variables
customer * custArray;       //An array of the customers
int custArraySize = 0;      //The size of the array of customers
deque<int> line1;      //The first line
deque<int> line2;      //The second line
deque<int> line3;      //The third line
deque<int> line4;      //The fourth line
deque<int> line5;      //The fifth line
double lineTime[5] = {0,0,0,0,0};      //The amount of time the current customer is taking to checkout 
double time = 0;            //Timer that increments everytime simulation is called
int numDoneShopping = 0;        //The number of customers who are done shopping, either by leaving line or finishing checking out
int numOfPeople;            //The total number of people
int numNotCheckedOut;       //The number of people who have not entered a line yet
const int MAX_LINE_LENGTH = 10;

const int MAX_CHECKOUT_TIME = 20;

int main(int argc, char **argv)
{
    numOfPeople = 0;
    
    
    cout<<"How many people should the grocery store checkout simulate?"<<endl;          //Prompt the user for input
    cin>>numOfPeople;       //Get user input
    
    
    
    generateCustomers(numOfPeople);
    simulate();
    
	
	return 0;
}

//Creates the customers with ids from 1 to the number that needs to be created
void generateCustomers(int numToCreate){
    assert(numToCreate > 1);
    
    custArray = new customer[numToCreate];
    for(int i = 0; i<numToCreate;i++){
        custArray[i] = customer(i+1);        //create a new customer and add them to the customer array
        custArraySize++;                       //Reflect the change in size
    }
    
    printArray();
    simulate();
}

//Gets a customer from the the custArray and if it is not already in checkout or checking out sends them to checkout
void moveToCheckout(bool force){
    int getCustomer = rand() % 2;       //Random value for it a customer is going to checkout
    int custIndex;      //The index of a customer selected to checkout
    customer* custToCheckout;        //The instance of the customer who is going to check out
    if(getCustomer == 1 || force){
        custIndex = rand( )% custArraySize;       //Gets a random index for a customer from the custArray
        custToCheckout = &custArray[custIndex];      //Get the customer at the current custIndex and assign the reference to custToCheckout
        //Check if the customer at that index is valid
        if(!custToCheckout->hasAlreadyEnteredLine()){
            //cout<<"hasAlreadyEnteredLine()"<<custToCheckout->hasAlreadyEnteredLine()<<endl;
           // cout<<"Customer : "<<custToCheckout.getID()<<" Entering the line"<<endl;
            custToCheckout->checkingOut() ;       //Set the customer as checking out
            //cout<<"hasAlreadyEnteredLine()"<<custToCheckout->hasAlreadyEnteredLine()<<endl;
            custToCheckout->setStartTime(time);
            sendToShortestLine(*custToCheckout);
            numNotCheckedOut--;
            custToCheckout = NULL;      //Set the cust to check to null
        }
        else{
            //If a customer was supposed to be sent to checkout but the one called has already entered the line recursively call
            //this function until it gets a valid customer
            //custToCheckout = NULL;  
            //moveToCheckout(true);
        }
    }

    
}


void simulate(){
    numNotCheckedOut = numOfPeople;
    //Run the simulation until everyone has checked out
    while(numDoneShopping < numOfPeople){
        time++;     //Increment the time
        leaveStore();       //Check if anyone is going to leave for waiting too long
        //Check if there are still customers that still need to checkout
        if( numNotCheckedOut > 0){
            //Random yes or no to get a customer from the available customers and check them out
            moveToCheckout(false);
        }
        checkOut();         //Run the line

        //moveLine();
    }
    //printArray();
}


void sendToShortestLine(customer cust){
    int line = getShortestLine();
    
    //switch used to select the line to send the customer too
    switch(line)
    {
        case 1:
            cout<<"Customer :"<<cust.getID()<<" entered line 1"<<"   time: "<<time<<endl;
            if(line1.size()<= MAX_LINE_LENGTH)
                {
                    cust.setStartTime(time);
                    line1.push_back(cust.getID());
                }
            else 
                {
                    cout<<"Cutomer: "<<cust.getID()<<" left because all the lines were too long"<<"   time: "<<time<<endl;       //print that the customer is leaving
                }
            
            break;        
        case 2:
            cout<<"Customer :"<<cust.getID()<<" entered line 2"<<"   time: "<<time<<endl;
                        if(line2.size()<= MAX_LINE_LENGTH)
                {
                    cust.setStartTime(time);
                    line2.push_back(cust.getID());
                }
            else 
                {
                    cout<<"Cutomer: "<<cust.getID()<<" left because all the lines were too long"<<"   time: "<<time<<endl;       //print that the customer is leaving
                }
            break;
        case 3:
            cout<<"Customer :"<<cust.getID()<<" entered line 3"<<"   time: "<<time<<endl;
                        if(line3.size()<= MAX_LINE_LENGTH)
                {
                    cust.setStartTime(time);
                    line3.push_back(cust.getID());
                }
            else 
                {
                    cout<<"Cutomer: "<<cust.getID()<<" left because all the lines were too long"<<"   time: "<<time<<endl;       //print that the customer is leaving
                }
            break;        
        case 4:
            cout<<"Customer :"<<cust.getID()<<" entered line 4"<<"   time: "<<time<<endl;
                        if(line4.size()<= MAX_LINE_LENGTH)
                {
                    cust.setStartTime(time);
                    line4.push_back(cust.getID());
                }
            else 
                {
                    cout<<"Cutomer: "<<cust.getID()<<" left because all the lines were too long"<<"   time: "<<time<<endl;       //print that the customer is leaving
                }
            break;
        case 5:
            cout<<"Customer :"<<cust.getID()<<" entered line 5"<<"   time: "<<time<<endl;
                        if(line5.size()<= MAX_LINE_LENGTH)
                {
                    cust.setStartTime(time);
                    line5.push_back(cust.getID());
                }
            else 
                {
                    cout<<"Cutomer: "<<cust.getID()<<" left because all the lines were too long"<<"   time: "<<time<<endl;       //print that the customer is leaving
                }
            break;
        
        
    }
    
    
    
}

//Compares the sizes of the lines and returns the number of the line that is the shortest
int getShortestLine(){
    int shortest;       //The index of the shortest line
    int sizes[5] = {line1.size(), line2.size(), line3.size(), line4.size(), line5.size()};
    
    shortest = 0;        //Set the first line as the shortest by default
    
    //Compare the lines and get the shortest one
    for(int i = 0; i < 5; i++){
        //If another line is shorter set its index as shortest
        if( sizes[i] < sizes[shortest] ){
            shortest = i;
        }
        
    }
    
    return shortest+1;
    
    
}


void moveLine(customer cust, int line){
    
    
}

//Checks all the lines to make sure they are checking someone out if they have customers
void checkOut(){

//Line1
    //Check if the line is not currently checking anyone out and if they have anyone in line
    if(lineTime[0] == 0 && line1.size()>0){
        //Set a random checkout time
        lineTime[0] = (rand( )%MAX_CHECKOUT_TIME)+time;
    }
    //Check if the current customer is done checking out
    else if(lineTime[0] <= time && line1.size()>0 ){
        lineTime[0] = 0;        //Set the line time to zero to signify that the next person needs to checkout
        cout<<"Customer :" << custArray[line1.front()-1].getID() <<" checked out at line1"<<"   time: "<<time<<endl;      //Print the customer that checked out to the console
        line1.pop_front();      //Remove the customer from the line
        numDoneShopping++;      //Increase the number of customers done shopping by one
    }

//Line2
    //Check if the line is currently checking anyone out and if they have anyone in line
    if(lineTime[1] == 0 && (line2.size() > 0)){
        //Set a random checkout time
        lineTime[1] = (rand( )%MAX_CHECKOUT_TIME)+time;
    }
    //Check if the current customer is done checking out
    else if(lineTime[1] <= time && (line2.size() > 0)){
        lineTime[1] = 0;        //Set the line time to zero to signify that the next person needs to checkout
        cout<<"Customer :" << custArray[line2.front()-1].getID() <<" checked out at line2"<<"   time: "<<time<<endl;      //Print the customer that checked out to the console
        line2.pop_front();      //Remove the customer from the line
        numDoneShopping++;      //Increase the number of customers done shopping by one
    }

//Line3
    //Check if the line is currently checking anyone out and if they have anyone in line
    if(lineTime[2] == 0 && line3.size()>0){
        //Set a random checkout time
        lineTime[2] = (rand( )%MAX_CHECKOUT_TIME)+time;
    }
    //Check if the current customer is done checking out
    else if(lineTime[2] <= time && line3.size()>0){
        lineTime[2] = 0;        //Set the line time to zero to signify that the next person needs to checkout
        cout<<"Customer :"<<custArray[line3.front()-1].getID() <<" checked out at line3"<<"   time: "<<time<<endl;      //Print the customer that checked out to the console
        line3.pop_front();      //Remove the customer from the line
        numDoneShopping++;      //Increase the number of customers done shopping by one
    }

//Line4
    //Check if the line is currently checking anyone out and if they have anyone in line
    if(lineTime[3] == 0 && line4.size()>0){
        //Set a random checkout time
        lineTime[3] = (rand( )%MAX_CHECKOUT_TIME)+time;
    }
    //Check if the current customer is done checking out
    else if(lineTime[3] <= time && line4.size()>0 ){
        lineTime[3] = 0;        //Set the line time to zero to signify that the next person needs to checkout
        cout<<"Customer :"<<custArray[line4.front()-1].getID() <<" checked out at line4"<<"   time: "<<time<<endl;      //Print the customer that checked out to the console
        line4.pop_front();      //Remove the customer from the line
        numDoneShopping++;      //Increase the number of customers done shopping by one
    }

//Line5
    //Check if the line is currently checking anyone out and if they have anyone in line
    if(lineTime[4] == 0 && line5.size()>0){
        //Set a random checkout time
        lineTime[4] = (rand( )%MAX_CHECKOUT_TIME)+time;
    }
    //Check if the current customer is done checking out
    else if(lineTime[4] <= time && line5.size()>0){
        lineTime[4] = 0;        //Set the line time to zero to signify that the next person needs to checkout
        cout<<"Customer :"<<custArray[line5.front()-1].getID() <<" checked out at line5"<<"   time: "<<time<<endl;      //Print the customer that checked out to the console
        line5.pop_front();      //Remove the customer from the line
        numDoneShopping++;      //Increase the number of customers done shopping by one
    }

    
}

//Checks the last customer in all the lines and if they have waited too long they leave
void leaveStore(){
    if(line1.size()> 0 && custArray[line1.back()].exceededWait(time)){
        cout<<"Cutomer: "<<custArray[line1.back()-1].getID()<<" waited too long and left"<<"   time: "<<time<<endl;       //print that the customer is leaving
        line1.pop_back();       //pop the last customer
    }
    if(line2.size() > 0 && custArray[line2.back()].exceededWait(time)){
        cout<<"Cutomer: "<<custArray[line2.back()-1].getID()<<" waited too long and left"<<"   time: "<<time<<endl;       //print that the customer is leaving
        line2.pop_back();       //pop the last customer
    }
    if(line3.size()> 0 && custArray[line3.back()].exceededWait(time)){
        cout<<"Cutomer: "<<custArray[line3.back()-1].getID()<<" waited too long and left"<<"   time: "<<time<<endl;       //print that the customer is leaving
        line3.pop_back();       //pop the last customer
    }
    if(line4.size()> 0 && custArray[line4.back()].exceededWait(time)){
        cout<<"Cutomer: "<<custArray[line4.back()-1].getID()<<" waited too long and left"<<"   time: "<<time<<endl;       //print that the customer is leaving
        line4.pop_back();       //pop the last customer
    }
    if(line5.size()> 0 && custArray[line5.back()].exceededWait(time)){
        cout<<"Cutomer: "<<custArray[line5.back()-1].getID()<<" waited too long and left"<<"   time: "<<time<<endl;       //print that the customer is leaving
        line5.pop_back();       //pop the last customer
    }
    
}

void printArray(){
    cout<<"custArraySize: "<<custArraySize<<endl;
    for (int i = 0; i < custArraySize ;i++){
        cout<<custArray[i].getID()<<endl;
    }
}