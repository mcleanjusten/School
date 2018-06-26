//Name: Justen mclean
//Assignment: Homework 6
//Class: TTH 6:30 p.m.
//File: main.cpp
//About: Provids the selection sort algorithm for sorting linked list that use a template parameter type.
//Testing: Testing of the selection sort method is provided by the test method.
//
//void sort_list(node*& head_ptr);
//Precondition: head_ptr is a head pointer of a linked list of items, and these
//items can be compared with a less-than operator.
//Postcondition: head_ptr points to the head of  a linked list with exactly the
//same entries (including repetion if any), but the entries in this list are sorted
//from smallest to largest.  The original linked list is no longer available.
//
//void printList(node*& head_ptr);
//Precondition: head_ptr is a head pointer of a linked list of items.
//Postcondition: All the nodes in the linked list have had there data() value printed to the console.
//
//void test();
//Precondition: The sort_list(node*& head_ptr) method must be available.
//Postcondition: Multiple list with different data_types and some repeating numbers must be created,
// sorted, and printed to the console.

#include <stdio.h> //Provides access to the standard assests
#include <node2.h> //provides access the the template version of the node class
#include <iostream> //Provides cout

using namespace std;
using namespace main_savitch_6B;

template <class Item>
void sort_list(node<Item>*& head_ptr);

template <class Item>
void printList(node<Item> * head_ptr);

void test();


int main(int argc, char **argv)
{
    //Call the test method
    test();


	return 0;
}

template <class Item>                  
void sort_list(node<Item>*& head_ptr){
    
    node<Item> *new_head_ptr;            //The second lists head_ptr
    node<Item> *cursor;                  //The current item of the first list
    node<Item> *previous;                //The previous item of the first list
    node<Item> *current_largest;         //The iterator that points to the current largest node, initially points to the head_ptr 
    node<Item> *current_previous;        //The iterator that points to the current largest node, initially points to the head_ptr
    bool firstNode = true;               //Is the item being inserted the first item in the list?

    
    while(head_ptr->link()!=NULL)        //While the head_ptr of the first linked list is still pointing at something
    {          
        //Reset the values to reflect the current loop
        current_largest = head_ptr;                
        current_previous = NULL;
        previous = NULL;
       
        
        //For loop to get the larget data item out of the first linked list
        for(cursor = head_ptr; cursor != NULL; cursor = cursor->link())
        {
            //Check if position if larger than the current largest node, if so make current_largest point to the node position is currently pointing too
            if((cursor->data()) > (current_largest->data()) ){
                current_largest = cursor;           //Set the current_largest node  = to position
                current_previous = previous;        //Set current_previous = to previous for easier removal
            }
            
            previous = cursor;                      //Set the previous node value
        }
        
        //Move the current_largest from the first list to the last position in the second list
        if((current_previous == NULL) && (head_ptr->link()!=NULL))           //Check if the largest node was the head of the first list
        {
            if(firstNode){                                                   //Set the node as the head node in the second list
                head_ptr = current_largest->link();                          //Remove current_largest from the original list
                current_largest->set_link(NULL);                             //Set the link to NULL since it is the largest item in the list
                new_head_ptr = current_largest;                              //Set the head of the new list = to the current largest
                firstNode = false;                                           //Set the firstNode flag to false
            }
            else                                                             //Move the node to the second list
            {                                                                
                head_ptr = current_largest->link();                          //Set the head_ptr to point at the item after current_largest in the list
                current_largest->set_link(new_head_ptr);                     //Set current_largest to link to the head of the second list
                new_head_ptr = current_largest;                              //Set the head of the second list to point to the current_largest value
            }   
        }
        
        else if((head_ptr->link()!=NULL))                                    //Set the current_largest node as the new head of the second list
        {
            if(firstNode)                                                    //Check if the second list has a head node
            {
                new_head_ptr = current_largest;                              //Set the head of the new list = to the current largest
                current_previous->set_link(current_largest->link());         //Remove current_largest from the original list
                current_largest->set_link(NULL);                             //Set the link to NULL since it is the largest item in the list
                firstNode = false;                                           //Set the firstNode flag to false            
            }
            else 
            {
                current_previous->set_link(current_largest->link());         //Set the head_ptr to point at the item after current_largest in the list
                current_largest->set_link(new_head_ptr);                     //Set current_largest to link to the head of the second list
                new_head_ptr = current_largest;                              //Set the head of the second list to point to the current_largest value
                
            }
        }

        
    }
    //The last item in head_ptr is the smallest item, so set its link to the head pointer of the new list and all the items are in order
    head_ptr->set_link(new_head_ptr);

}

//Prints the linked list when given a pointer
template <class Item>
void printList(node<Item> * head_ptr){

    int listsize = list_length(head_ptr);
    if(listsize == 0){
        cout<< "List size 0"<<endl;
        return;
    }
    //Print the linked list to the console
    for(int j = 1; j<=listsize;j++){
        node<Item> * node_ptr = list_locate(head_ptr, j);
        cout<<"Node: "<<j<<" Data: "<<node_ptr->data()<<endl;
    }
    
}

//Test the sort_list() method above
void test(){
     
//    
//Doubles test 
// 
    cout<<"Double Test"<<endl;
   //Create a new double linked list with a repeating value
    node<double> * head_ptr = new node<double>(12);     //Create a new pointer node
    
    //Insert some double values 
    list_head_insert(head_ptr, 3.5);
    list_head_insert(head_ptr, 7.5);
    list_head_insert(head_ptr, 2.5);
    list_head_insert(head_ptr, 11.5);
    list_head_insert(head_ptr, 11.5);
    list_head_insert(head_ptr, 13.5);
    list_head_insert(head_ptr, 30.5);
    
    //Print the values of the list before they run through the sorting algorithm
    cout<<"Unsorted double list start"<<endl;
    printList(head_ptr);
    cout<<"Unsorted list end"<<endl;
    cout<<endl;
    sort_list(head_ptr);                                //Call sort_list on the double list
    
    //Print the sorted double values
    cout<<"Sorted double list start"<<endl;
    printList(head_ptr);
    cout<<"Sorted double list end"<<endl;
    cout<<endl;
    cout<<endl;
    
//
//Float test
//

    cout<<"Float Test"<<endl;
   //Create a new float linked list with a repeating value
    node<float> * float_head_ptr = new node<float>(7);     //Create a new pointer node
    
    //Insert some double values 
    list_head_insert(float_head_ptr, 3.5f);
    list_head_insert(float_head_ptr, 5.6f);
    list_head_insert(float_head_ptr, 1.2f);
    list_head_insert(float_head_ptr, 15.0f);
    list_head_insert(float_head_ptr, 11.77f);
    list_head_insert(float_head_ptr, 13.5f);
    list_head_insert(float_head_ptr, 3.5f);
    list_head_insert(float_head_ptr, 2.0f);
    
    //Print the values of the list before they run through the sorting algorithm
    cout<<"Unsorted float list start"<<endl;
    printList(head_ptr);
    cout<<"Unsorted float list end"<<endl;
    cout<<endl;
    sort_list(head_ptr);                                //Call sort_list on the double list
    
    //Print the sorted double values
    cout<<"Sorted float list start"<<endl;
    printList(head_ptr);
    cout<<"Sorted float list end"<<endl;
    cout<<endl;
    cout<<endl;
    
//
//Int test
//

    cout<<"Int Test"<<endl;
   //Create a new int linked list with a repeating value
    node<int> * int_head_ptr = new node<int>(7);     //Create a new pointer node
    
    //Insert some double values 
    list_head_insert(int_head_ptr, 3);
    list_head_insert(int_head_ptr, 5);
    list_head_insert(int_head_ptr, 1);
    list_head_insert(int_head_ptr, 135);
    list_head_insert(int_head_ptr, 101);
    list_head_insert(int_head_ptr, 10);
    list_head_insert(int_head_ptr, 3);
    list_head_insert(int_head_ptr, 28);
    
    //Print the values of the list before they run through the sorting algorithm
    cout<<"Unsorted int list start"<<endl;
    printList(head_ptr);
    cout<<"Unsorted int list end"<<endl;
    cout<<endl;
    sort_list(head_ptr);                                //Call sort_list on the double list
    
    //Print the sorted double values
    cout<<"Sorted int list start"<<endl;
    printList(head_ptr);
    cout<<"Sorted int list end"<<endl;
    
}