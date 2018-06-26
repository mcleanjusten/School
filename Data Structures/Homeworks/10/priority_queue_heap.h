#ifndef PRIORITY_QUEUE_HEAP_H
#define PRIORITY_QUEUE_HEAP_H

template <class T>
class priority_queue_heap {
    

public:
    priority_queue_heap(){
        m_heap = new heap<int>();
    }
    bool is_empty() const{ return m_heap.is_empty();};

    bool is_full() const{ return m_heap.is_full();};

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
     heap<T> m_heap;
    };



#include "priority_queue_heap.template"
//#inlcude "heap.h"

#endif // PRIORITY_QUEUE_HEAP_H
