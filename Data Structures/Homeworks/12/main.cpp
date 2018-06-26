//Name: Justen McLean
//Assignment: Homework 12


#include <stdio.h>

#include <algorithm>  // Provides swap
#include <cstdlib>    // Provides EXIT_SUCCESS, size_t
#include <iostream>   // Provides cout and cin

using namespace std;

// PROTOTYPES of the functions used in this test program:
void insertionsort(int data[ ], size_t n);
// Precondition: data is an array with at least n components.
// Postcondition: The elements of data have been rearranged so
// that data[0] <= data[1] <= ... <= data[n-1].


int main( )
{
    const char BLANK = ' ';
    const size_t ARRAY_SIZE = 10;  // Number of elements in the array to be sorted
    int data[ARRAY_SIZE];          // Array of integers to be sorted
    int user_input;                // Number typed by the user
    size_t number_of_elements;     // How much of the array is used
    size_t i;                      // Array index

    // Provide some instructions
    cout << "Please type up to " << ARRAY_SIZE << " positive integers.";
    cout << "Indicate the list's end with a zero." << endl;

    // Read the input numbers
    number_of_elements = 0;
    cin >> user_input;
    while ((user_input != 0) && (number_of_elements < ARRAY_SIZE))
    {
        data[number_of_elements] = user_input;
        number_of_elements++;
        cin >> user_input;
    }

    // Sort the numbers and print the result with two blanks after each number
    insertionsort(data, number_of_elements);
    cout << "In sorted order, your numbers are: " << endl;
    for (i = 0; i < number_of_elements; i++)
        cout << data[i] << BLANK << BLANK;
    cout << endl;

    return EXIT_SUCCESS;
}

//The modified insertionsort
void insertionsort(int data[], size_t n)
{
    int step_size = n/2;
    
    while(step_size>0)
    {
        //SelectionSort on elements in the current stepsize
        for(int i = 0; i < n; i++)
        {
            
            for(int j = 1; j < n; j++)
            {
                int it = 1;
                int current_index = i+(j*step_size);
                int last_index = i+((j-it)*step_size);

                //Make sure index is within the bounds of the array
                if(current_index < n){
                    //cout<<"J: "<<j<<" Current index: "<<data[current_index]<<" Last index: "<<data[last_index]<<endl;
                    //Check if the current index needs to be inserted 
                    while(data[current_index]<data[last_index])
                    {
                        //Swap positions with the last index until its correctly in the sorted part of this step_size
                        swap(data[current_index], data[last_index]);
                     
                        //Set current_index = to last_index
                        current_index = last_index;
                        it++;
                        last_index = i+((j-it)*step_size);
                        if(last_index < 0){
                            //If last index gets below the minimum position of the array break while loop
                            break;
                        }
                    }
                }
                
                
                
            }
            
            
        }
        
        cout << "In "<<step_size<<"-sorted order, your numbers are: " << endl;
        for (int i = 0; i < n; i++)
            cout << data[i] << " " << " ";
        cout << endl;
        
        //Get the next step size
        step_size = step_size/2.2;
    }
    
    
    
}