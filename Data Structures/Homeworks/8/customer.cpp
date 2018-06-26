//Name: Justen mclean
//Assignment: Homework 8
//Class: TTH 6:30 p.m.
//File: customer.cpp
//About: This class creates a new customer for the grocery simulation program

#include "customer.h"
using namespace Mclean_Homework8;

const int MAX_WAIT_TIME = 20;

customer::customer()
{
    id = 0;
    checkedOut = false;
}

customer::customer(int customer_id){
    id = customer_id;
    checkedOut = false;
}

customer::~customer()
{
    
}

void customer::setStartTime(int startTime) { 
    wait_start = startTime; 
    }
    
    
bool customer::exceededWait(int currentTime){ 
    if((wait_start+MAX_WAIT_TIME) <= currentTime)
        {
        return true;
        }
    else
        {
            return false;
        }
 }
void customer::checkingOut()
    {
    checkedOut = true;
    }
bool customer::hasAlreadyEnteredLine()
    { 
        if(checkedOut == true){
            return true;
        } 
        
        else { 
            return false;
            } 
}