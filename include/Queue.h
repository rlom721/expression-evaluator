// Specification file for Queue class
//
// The Queue class is and inherited class from List class.
// Features include enqueue, dequeue, search and sort methods.

#ifndef QUEUE_H
#define QUEUE_H

#include "List.h"    // header file for ListItem class
namespace lomboy_a2 {

    template <class DataType>
    class Queue : public List<DataType> {
    public:
        // typedef
        typedef DataType queueDataType;
        // Constructors
        Queue();
        Queue(queueDataType& entry);
        Queue(const Queue&);    // copy
        // Modification methods
        void enqueue(queueDataType entry);
        queueDataType dequeue();
        void sort();            // default sorts ascending
        void sortDsc();
        // Constant methods
        bool searchQ(int key);
        bool isEmpty() const;
        bool isFull() const;
    private:
        int size;
    };

}

#endif