#ifndef HEAP_H
#define HEAP_H

/**
 * This class implements a heap as described in the text.
 * We will treat it as a priority queue.
 */

template <class T>
class heap {
public:
    static const int CAPACITY = 10;

    heap() {
        size = 0;
    }

    bool is_empty() const { return  size == 0;}
    bool is_full() const { return size == CAPACITY; }

    /**
     * Remove the largest value from this heap and return it.
     *
     * Precondition: heap is not empty.
     */
    T remove();

    /**
     * Inserts the 'value' into the heap.
     *
     * Precondition: heap is not full
     */
    void insert(const T& value);


    /**
     * Check if the heap is valid.
     * Prints out each parent and its children (for all nodes with children)
     * Stops when a parent is less than one or both of its children
     * Prints 'check' for each parent that is greater than or equal to its children
     */
    bool check_heap();

private:
    T data[CAPACITY];
    int size;
};

#include "heap.template"


#endif // HEAP_H
