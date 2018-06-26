//Name: Justen McLean
//Assignment: Homework 5
//Class: Data structures TTH 6:30 pm
//File: main.cpp

#include <stdio.h>
#include <node1.h>
#include <iostream>     //provides cout
#include <cstdlib>      //rand()

using namespace main_savitch_5;
using namespace std;

//Method declarations
void partOne();     //Part one of the homework
//Sets up the needed enviorment for the first part of the assignment
void partTwo();     //Part two of the homework
//Sets up the needed enviorment for the second part fo the assignment
void partThree();   //Part three of the homework
//Sets up the needed enviorment for the thrid part of the assignment
void printList(node * head_ptr);
//Precondition- takes in a linked list header pointer
//Postcondition- prints the list to the command line
node* joinList(node * head_ptr_a, node * head_ptr_b);
//Precondition- takes in two list head_ptr's
//Postcondition- combines the list and 
//returns the head_ptr to the new list
void listSplitter(node* head_ptr, double splitValue);
//Precondition- takes in a linked list header pointer
//Postcondition- splits the list into two list based
//on wether they are below the splitValue or not
void dupeRemover(node * head_ptr);
//Precondition- takes in a linked list header pointer
//Postcondition- removes duplicate nodes from the list



const int SIZE = 20;        //Size of the generated array for part 1
const double SPLIT = 3.5;   //The split value for part 3


int main(int argc, char **argv)
{
    cout<<"Part one of HW assignment"<<endl;
    partOne();
    cout<<endl;
    
    cout<<"Part two of HW assignment"<<endl;
    partTwo();
    cout<<endl;
    
    cout<<"Part threee of the HW assignement"<<endl;
    partThree();
    cout<<endl;
    
    
    
	return 0;
}

//Part one of the homework
void partOne(){
    node * new_node;    //Pointer for new nodes          
	node * head_ptr = new node(1);      //Create a head_ptr node
    int listLength;     //Get the size of the list
    
    //Generate a linked list with random data values
    for(int i = 0;i<=SIZE;i++){
        new_node = new node(rand()%10+1,head_ptr);      //Give the node a random value between 1 and 10 and link to head_ptr
        head_ptr = new_node;      //Set the head_ptr to the new node that was just inserted in the front
    }
    listLength = list_length(head_ptr);     //Get the size of the list
    
    //Tell the user what the data is
    cout<<"Linked list generated with random int between 1 and 10"<<endl;
    printList(head_ptr);
    cout<<"List Length is: "<<listLength<<endl;
    
    //Call duplicate remover
    dupeRemover(head_ptr);
    //Print the deduplicated list out
    printList(head_ptr);
    listLength = list_length(head_ptr);     //Get the size of the list
    cout<<"List Length is: "<<listLength<<endl;     //Print the list length
    
}

//Shows part two of the homework
void partTwo(){
    node * new_node;    //Pointer for new nodes          
	node * head_ptr_a = new node(1);      //Create a head_ptr node
    node * head_ptr_b = new node(1);      //Create a head_ptr node
    int listLengthA;     //Get the size of the list a
    int listLengthB;     //Get the size of the list b
    
//Generating two linked list    
    
    //Generate a linked list with values counting from SIZE down too 1 for list A
    for(int i = 40;i>0;i-=2){
        new_node = new node(i,head_ptr_a);      //Give the node a random value between 1 and 10 and link to head_ptr
        head_ptr_a = new_node;      //Set the head_ptr to the new node that was just inserted in the front
    }
    listLengthA = list_length(head_ptr_a);      //Get the size of list a
    
    //Generate a linked list with values counting from SIZE down too 1 for list B
    for(int i = 40;i>0;i-=3){
        new_node = new node(i,head_ptr_b);      //Give the node a random value between 1 and 10 and link to head_ptr
        head_ptr_b = new_node;      //Set the head_ptr to the new node that was just inserted in the front
    }
    listLengthB = list_length(head_ptr_b);     //Get the size of list b
    
//Printing the list information to the screen
    
    //Tell the user what the data is
    cout<<"Linked list A is "<<endl;
    printList(head_ptr_a);
    cout<<"List Length  is: "<<listLengthA<<endl;
    cout<<endl;
    
    //Tell the user what the data is
    cout<<"Linked list B is "<<endl;
    printList(head_ptr_b);
    cout<<"List Length  is: "<<listLengthB<<endl;
    cout<<endl;
    
    //Call joinList to create a new list
    node * join_head_ptr;
    join_head_ptr = joinList(head_ptr_a,head_ptr_b);
    
    //Print the deduplicated list out
    printList(join_head_ptr);
    int listLength = list_length(join_head_ptr);     //Get the size of the list
    cout<<"List Length is: "<<listLength<<endl;     //Print the list length
}

//Shows part three of the homework
void partThree(){
    node * new_node;    //Pointer for new nodes          
	node * head_ptr = new node(1);      //Create a head_ptr node
    int listLength;     //Get the size of the list
    
    //Generate a linked list with random data values
    for(int i = 0;i<=SIZE;i++){
        new_node = new node(rand()%10+1,head_ptr);      //Give the node a random value between 1 and 10 and link to head_ptr
        head_ptr = new_node;      //Set the head_ptr to the new node that was just inserted in the front
    }
    listLength = list_length(head_ptr);     //Get the size of the list
    
    //Tell the user what the data is
    cout<<"Linked list generated with random int between 1 and 10"<<endl;
    printList(head_ptr);
    cout<<"List Length is: "<<listLength<<endl;
    
    //Call the function to split the list into two list
    listSplitter(head_ptr, SPLIT);
    
}


//Removes duplicate items from a linked list
//Problem 2 from pg.287
void dupeRemover(node * head_ptr){
    node * currentNode;         //The node whos value is being checked for duplicates
    node * nodeToCheck;         //The node to compare current node too
    int nodeCount = 0;          //The number of times a node appears
    int listLength = list_length(head_ptr);     //Get the size of the list
    cout<<endl;
    cout<<"Removing Duplicate Nodes"<<endl;    
    
    for(int i = 1;i <=listLength;i++){         //Loop through one half of the list, after getting halfway all values will have been checked
        currentNode = list_locate(head_ptr,i);                  //Get the node located at i
        for(int j = 1;j<=listLength;j++ ){
            nodeToCheck = list_locate(head_ptr, j);             //Get the node located at iterator j
            
            if(currentNode->data() == nodeToCheck->data()){                     //Check if the the node is a duplicate
                nodeCount++;
                
                if(nodeCount>=2){                               //If this is the second or more time this node has occured delete it
                    list_remove(list_locate(head_ptr,j-1));     //Remove the node
                    listLength--;                               //decrease the list size 
                }
            }
                                               //Reset the node count
        }
        nodeCount = 0;   
    }
    
}

//Funciton that combines two list that are ordered in least to greatest and removes any dulplicates
//Problem 5 on page 287
node* joinList( node * head_ptr_a, node * head_ptr_b){
    node * new_head_ptr = new node(100);        //pointer for the new linked list
    node * new_current_ptr = new_head_ptr;     //pointer for the current item of the new linked list
    node * new_node;
    node * current_a = list_locate(head_ptr_a,1);           //pointer to the current a node
    node * current_b = list_locate(head_ptr_b,1);           //pointer to the current b node
    int incrementA = 1;         //The position of the current node for list a
    int incrementB = 1;         //The position of the current node for list b
    bool go = true;
    
    cout<<"Merging List"<<endl;
    
    //Loop to check and insert the nodes
    while((current_a->link()!=NULL)&&(current_b->link()!=NULL)&&go){
        
        //if the current value of b is smaller insert it otherwise insert A
        if(current_a->data() >= current_b->data()){
            
            new_node= new node(current_b->data());      //New node with data = current b
            new_current_ptr->set_link(new_node);        //link to the new node
            new_current_ptr = new_current_ptr->link();  //set current node to the new node
            incrementB++;
            current_b = list_locate(head_ptr_b, incrementB);      //Update the value of current_b
        }
        else if( current_a->data() < current_b->data())
        {
            
            new_node= new node(current_a->data());              //New node with data = current a
            new_current_ptr->set_link(new_node);                //link to the new node
            new_current_ptr = new_current_ptr->link();          //set current node to the new node
            incrementA++;
            current_a = list_locate(head_ptr_a, incrementA);      //Update the value of current_a
        }
        else
            go = false;
    }
    cout<< "Out of main While"<<endl;
    //Check that there are no more nodes in list a
    while(current_a->link()!=NULL){
            new_node= new node(current_a->data());              //New node with data = current a
            new_current_ptr->set_link(new_node);                //link to the new node
            new_current_ptr = new_current_ptr->link();          //set current node to the new node
            incrementA++;
            current_a = list_locate(head_ptr_a, incrementA);      //Update the value of current_a
    }
    
    //Check that there are no more nodes in list b
    while(current_b->link()!=NULL){
            new_node= new node(current_b->data());              //New node with data = current a
            new_current_ptr->set_link(new_node);                //link to the new node
            new_current_ptr = new_current_ptr->link();          //set current node to the new node
            incrementB++;
            current_b = list_locate(head_ptr_b, incrementB);      //Update the value of current_b
    }
    
    
    //Remove the head_ptr space holder created at the beggining
    new_current_ptr = new_head_ptr->link();
    list_remove(new_head_ptr);
    new_head_ptr = new_current_ptr;
    
    dupeRemover(new_head_ptr);      //Remove any duplicates
    
    //printList(new_head_ptr);
    return new_head_ptr;
    
}

//Splits a linked list into two list based on the split value, one list only contains the nodes with values below the split value
void listSplitter(node* head_ptr, double splitValue){
    node* less_head_ptr = new node();            //Head pointer for the less than list
    node* current_node_ptr = head_ptr;         //The current node poitner
    node* previous_node_ptr;                   //Used to hold the previous node for calling list_remove
    node* new_node;                 //Used to create a copy of nodes that will be moved to  the less than list
    int size;                       //The size of the original list
    
    
    //Loop checks each item in the original list to see if it is below the splitValue, if so a new node with the same data
    //is linked to the less than list while the original node is destroyed
    while(current_node_ptr->link() != NULL){
        //If the node is below the split value
        if(current_node_ptr->data() < splitValue){
            //Add the node to the less linked list
            new_node = new node(current_node_ptr->data(),less_head_ptr);
            less_head_ptr = new_node;       //Set less_head_ptr back to the head of the list
        
            //Check if current_node_ptr is the head of the list
            if(current_node_ptr == head_ptr){
                head_ptr = head_ptr->link();        //Set head_ptr to the next node in the list
                list_head_remove(current_node_ptr);      //Remove the previous head pointer
            }
            else{
                current_node_ptr = current_node_ptr->link();    //Move the current_node_ptr to the next  node
                list_remove(previous_node_ptr);                 //Removes the node that was below splitValue from the current list
            }
        }
        else{
            previous_node_ptr=current_node_ptr;         //Set previous_node_ptr to the value of current_node_ptr
            current_node_ptr=current_node_ptr->link();      //Move current_node_ptr to the next node in the lsit
            
        }
    }
    
    //Remove the space holder node for less_head_ptr
    current_node_ptr = less_head_ptr->link();
    list_remove(less_head_ptr);
    less_head_ptr = current_node_ptr;
    
    
    //Format and print the list above the split
    cout<<endl;
    cout<<"List above the split"<<endl;
    printList(head_ptr);
    cout<<"List length is: "<<list_length(head_ptr)<<endl;
    cout<<endl;
    
    //Format and print the list below the split
    cout<<endl;
    cout<<"List below the split"<<endl;
    printList(less_head_ptr);
    cout<<"List length is: "<<list_length(less_head_ptr)<<endl;
    cout<<endl;
    
    
}
    



//Prints the linked list when given a pointer
void printList(node * head_ptr){
    int listsize = list_length(head_ptr);
    //Print the linked list to the console
    for(int j = 1; j<=listsize;j++){
        node * node_ptr = list_locate(head_ptr, j);
        cout<<"Node: "<<j<<" Data: "<<node_ptr->data()<<endl;
    }
    
}