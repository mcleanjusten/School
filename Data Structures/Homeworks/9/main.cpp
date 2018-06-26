//Name: Justen mclean
//Assignment: Homework 9
//Class: TTH 6:30 p.m.
//File: main.cpp
//About: This class takes an ordered linked list and converts it to a balanced binary search tree
//
//template<class Item>
//void createSortedList(int length, node<Item> *& list_head_ptr);
//Precondition: needs to be passed a positive length and a reference to a linked_list head ptr
//Postcondition: generates a linked list with the specified number of items and values starting with 1 and ending at the specified length
//
//template<class Item>
//binary_tree_node<Item>* createBalancedTree(node<Item> * list_head_ptr);
//Precondition: list_head_ptr must be valid and not null
//Postcondition: creates the tree root and creates the left and right subtrees
//
//template<class Item>
//binary_tree_node<Item>* createBalancedSubTree(node<Item> * list_head_ptr);
//Precondition: list_head_ptr must be valid and not null and non zero
//Postcondition: creates a sub tree root and recursively creates any children elements
//
//template<class Item>
//void printTree(binary_tree_node<Item> * node_ptr);
//Precondition: node_ptr must not be null
//Postcondition: prints out the the binary search tree inorder


#include <stdio.h>
#include "node2.h"
#include "bintree.h"

//Needed namespaces
using namespace std;
using namespace main_savitch_6B;
using namespace main_savitch_10;

//Method declarations
template<class Item>
void createSortedList(int length, node<Item> *& list_head_ptr);
template<class Item>
binary_tree_node<Item>* createBalancedTree(node<Item> * list_head_ptr);
template<class Item>
binary_tree_node<Item>* createBalancedSubTree(node<Item> * list_head_ptr);
template<class Item>
void printTree(binary_tree_node<Item> * node_ptr);

int j = 0;

int main(int argc, char **argv)
{
    int size;
    node<int> * list_head_ptr;
    binary_tree_node<int> * bst;
    cout<<"How long should the list be?"<<endl;
    cin>>size;
    createSortedList(size, list_head_ptr);
    bst = createBalancedTree(list_head_ptr);
    printTree(bst);
    
	//printf("hello world\n");
	return 0;
}

template<class Item>
void createSortedList(int length,node<Item> *& list_head_ptr)
{
        node<Item> * previous_ptr;
        //Create the first item in the list
        list_head_insert(list_head_ptr, 1);
        //Set the previous_ptr to point to the head_ptr
        previous_ptr = list_head_ptr;
        
        cout<<"List in order: "<<endl;
        //Generate nodes and add them to the list
        for(int i = 2; i<length;i++){
            node<Item> * new_node = new node<Item> (i);
            //Add a new element to the list
            previous_ptr->set_link(new_node);
            //Set previous_ptr to the newest item
            previous_ptr = previous_ptr->link();
        }
        previous_ptr = list_head_ptr;
        for(int i = 1; i<length;i++){
            //Add a new element to the list
            cout<<previous_ptr->data()<<endl;
            //Set previous_ptr to the newest item
            previous_ptr = previous_ptr->link();
        }
        cout<<endl;
        cout<<"Tree output: "<<endl;

    
    
}

//Take an already sorted list and creates a balanced binary search tree from it
template<class Item>
binary_tree_node<Item>* createBalancedTree(node<Item> * list_head_ptr)
{
        

        //Get the size of the list
        int listSize = list_length(list_head_ptr);
        int middleElement = (int) (listSize/2 + 0.5);
        
        //Get the middle node and make it the binary_tree_root
        node<int> * middle_node = list_locate(list_head_ptr, middleElement);        //The node in the middle of the linkd_list
        binary_tree_node<Item> * root_ptr = new binary_tree_node<Item>(middle_node->data());       //Create the root of the binary search tree
        binary_tree_node<Item> * left_subtree_ptr;
        binary_tree_node<Item> * right_subtree_ptr;
        
        //Create a left list and a right list
        node<int> * left_head_ptr = list_head_ptr; 
        node<int> * right_head_ptr = middle_node->link();
        node<int> * left_tail_ptr = left_head_ptr;
        
        //Break the link in the linked list
        for(int i = 0; i < middleElement-1;i++){
            left_tail_ptr = left_tail_ptr->link();
        }
        //Set the link on the item before the middle to null to create a new list of all the item from the head to the last element before the middle node
        left_tail_ptr->set_link(NULL);
        //Create the left subtree and the right subtree
        left_subtree_ptr = createBalancedSubTree(left_head_ptr);
        right_subtree_ptr = createBalancedSubTree(right_head_ptr);
        
        //Set the left and right subtrees
        root_ptr->set_left(left_subtree_ptr);
        root_ptr->set_right(right_subtree_ptr);
         
        return root_ptr;
}


//Create a subtree when given a linked list
template<class Item>
binary_tree_node<Item>* createBalancedSubTree(node<Item> * list_head_ptr)
{
        //Variables
        binary_tree_node<Item> * root_ptr;
        binary_tree_node<Item> * left_subtree_ptr;
        binary_tree_node<Item> * right_subtree_ptr;
        node<Item> * middle_node_ptr;
        
        //Get the size of the list
        int listSize = list_length(list_head_ptr);
        
        //Recursion exit conditions
        //Make sure the list is not empty
        if(listSize == 0){

        }
        else if(listSize == 1){
            //If the list is only a single element return that element as a new tree node

            root_ptr = new binary_tree_node<Item> (list_head_ptr->data());
            return root_ptr;
        }
        else if(listSize == 2){
            root_ptr = new binary_tree_node<Item> (list_head_ptr->data());
            right_subtree_ptr = new binary_tree_node<Item> (list_head_ptr->link()->data());
            root_ptr->set_left(right_subtree_ptr);
            return root_ptr;
        }
        
        //Recursion base condition
        int middleElement = (int) (listSize/2 + 0.5);

        middle_node_ptr = list_locate(list_head_ptr, middleElement);
        root_ptr = new binary_tree_node<Item> (middle_node_ptr->data());
        
        
        //Create a left list and a right list
        node<int> * left_head_ptr = list_head_ptr; 
        node<int> * right_head_ptr = middle_node_ptr->link();
        
        node<int> * left_tail_ptr = left_head_ptr;
        
        //Break the link in the linked list
        for(int i = 0; i < middleElement;i++){
            left_tail_ptr = left_tail_ptr->link();
        }
        
        //Set the link on the item before the middle to null to create a new list of all the item from the head to the last element before the middle node
        left_tail_ptr->set_link(NULL);
        //Create the left subtree and the right subtree
        if(list_length(left_head_ptr) > 0)
            left_subtree_ptr = createBalancedSubTree(left_head_ptr);
        if(list_length(right_head_ptr) > 0)
            right_subtree_ptr = createBalancedSubTree(right_head_ptr);
        
        //Set the left and right subtrees
        root_ptr->set_left(left_subtree_ptr);
        root_ptr->set_right(right_subtree_ptr);

        return root_ptr;
        
}

template<class Item>
void printTree(binary_tree_node<Item> * node_ptr)
{
        if (node_ptr != NULL)
        {
            printTree( node_ptr->left( ));
            cout<< node_ptr->data()<<endl;
            printTree( node_ptr->right( ));
        }
}
