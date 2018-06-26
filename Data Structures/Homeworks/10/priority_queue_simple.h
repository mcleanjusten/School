#ifndef PRIORITY_QUEUE_SIMPLE_H
#define PRIORITY_QUEUE_SIMPLE_H

/**
 * This class implements a priority queue using a very simple strategy:
 * Store the values in an array.
 * Add new values at the end.
 * When asked to remove a value, search for the largest (linear search)
 *
 */

template <class T>
class priority_queue_simple {
public:
    static const int CAPACITY = 30;

    priority_queue_simple() {
        size = 0;
    }

    bool is_empty() const {
        return  size == 0;
    }

    bool is_full() const {
        return size == CAPACITY;
    }

    /**
     * Remove the largest value from this priority queue and return it.
     *
     * Precondition: priority queue is not empty.
     */
    T remove();

    /**
     * Inserts the 'value' into the priority queue.
     *
     * Precondition: priority queue is not full
     */
    void insert(const T& value);



private:
    T data[CAPACITY];
    int size;
};

#include "priority_queue_simple.template"


#endif // PRIORITY_QUEUE_SIMPLE_H
