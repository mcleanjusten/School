/**
 * Insert a few elements into a heap and the remove them
 * one by one and see if we get them in the right.
 */

#include "heap.h"
#include "priority_queue_heap.h"
#include "priority_queue_simple.h"
#include <iostream>
#include <ctime>
using namespace std;

void test1() {
    heap<int> hp;
    hp.insert(1);
    hp.insert(2);
    hp.insert(3);
    hp.insert(4);
    hp.insert(5);
    hp.check_heap();

    int x = hp.remove();
    cout << "removed " << x << endl;
    x = hp.remove();
    cout << "removed " << x << endl;
    x = hp.remove();
    cout << "removed " << x << endl;
    x = hp.remove();
    cout << "removed " << x << endl;
    x = hp.remove();
    cout << "removed " << x << endl;

    cout << "empty? " << hp.is_empty() << endl;

}

void test2() {
    srand(time(NULL));
    heap<int> hp2;
    for(int i = 0; i < 30; i++ ) {
        hp2.insert(rand());
    }
    while(!hp2.is_empty()) {
        int x = hp2.remove();
        cout << "removed " << x << endl;
    }

}

//Test the priority_queue_heap
void test3(){
    priority_queue_heap<int> * pqhp;
    cout<<"help"<<endl;
    pqhp->insert(1);
    cout<<"help1"<<endl;
    pqhp->insert(2);
    pqhp->insert(3);
    pqhp->insert(4);
    pqhp->insert(5);
    
    int x = pqhp->remove();
    cout << "removed " << x << endl;
    x = pqhp->remove();
    cout << "removed " << x << endl;
    x = pqhp->remove();
    cout << "removed " << x << endl;
    x = pqhp->remove();
    cout << "removed " << x << endl;
    x = pqhp->remove();
    cout << "removed " << x << endl;

    cout << "empty? " << pqhp->is_empty() << endl;
    
    
}

//Test the priority_queue_simple
void test4(){
    
}

int main() {
    cout<<"Test1"<<endl;
    //test1();
    cout<<"Test2"<<endl;
    //test2();
    cout<<"Test3"<<endl;
    test3();
    cout<<"Test4"<<endl;
    test4();
}