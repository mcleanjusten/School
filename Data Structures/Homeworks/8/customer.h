//Name: Justen mclean
//Assignment: Homework 8
//Class: TTH 6:30 p.m.
//File: customer.h
//About: This class creates a new customer for the grocery simulation program
//
//
//void setStartTime(int startTime);
//Precondition: startTime must be a positive integer
//Postcondition: sets the private member variable wait_start to the value of start time
//
//bool exceededWait(int currentTime);
//Precondition: currentTime must be the current in game time
//Postcondition: returns a bool of the value of if the player has exceeded the max time they will wait
//
//void checkingOut();
//Postcondition: Sets the chedOut value to true
//
//bool hasAlreadyEnteredLine();
//Postcondition: returns the private member variable checkedOut
//
//
//int getID(){ return id; }
//Postcondition: returns the id of the customer
//




#ifndef CUSTOMER_H
#define CUSTOMER_H

namespace Mclean_Homework8
{


    class customer
    {
        public:
            //Constructors
            customer();
            customer(int customer_id);
            ~customer();
            //
            void setStartTime(int startTime);
            bool exceededWait(int currentTime);
            void checkingOut();
            bool hasAlreadyEnteredLine();
            int getID(){ return id; }
        private:
            //Private member variables
            int id;
            int max_wait;
            int wait_start;
            bool checkedOut;
            
    };

}

#endif // CUSTOMER_H
