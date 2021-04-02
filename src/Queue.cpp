// Implementation file for Queue class
// File name: Queue.cpp

#include "List.h"        // header file for List class
#include "Queue.h"       // header file for Queue class
#include <iostream>
using namespace std;
namespace lomboy_a2 {

    // Default constructor sets default values of members
    template <class DataType>
    Queue<DataType>::Queue() : size(0) { }

    // Parametrized constructor sets default values of members, then inserts a new
    // entry into list.
    template <class DataType>
    Queue<DataType>::Queue(queueDataType& entry) : size(0) { 
        enqueue(entry);
    }

    // Copy constructor calls base class copy constructor
    template <class DataType>
    Queue<DataType>::Queue(const Queue& s) : List<DataType>(s) {}

    // This method adds an entry to the back of the Queue.
    template <class DataType>
    void Queue<DataType>::enqueue(queueDataType entry) {
        this->insertToTail(entry);
        size = this->getSize();
    }

    // This method removes an entry from the front of the Queue and returns it.
    template <class DataType>
    typename Queue<DataType>::queueDataType Queue<DataType>::dequeue() {
        typename List<DataType>::iterator frontItem = this->start();        // assign iterator to front item
        queueDataType frontData = *frontItem; // store data of item to return after deletion

        // remove item and update size
        this->removeHead();
        size = this->getSize(); 

        return frontData;
    }

    // This method sorts the items in the queue in ascending order.
    template <class DataType>
    void Queue<DataType>::sort() {
        this->sortAsc();
    }

    // This method sorts the items in the queue in descending order.
    template <class DataType>
    void Queue<DataType>::sortDsc() {
        this->sortDesc();
    }

    // This method searches for item with matching key in queue.
    template <class DataType>
    bool Queue<DataType>::searchQ(int key) {
        return this->search(key);
    }

    // This method returns true if queue is empty.
    template <class DataType>
    bool Queue<DataType>::isEmpty() const { 
        return (size == 0); 
    }

    // This method returns true if there is no space to allocate a new item on Queue<DataType>.
    // It also throws an exception to indicate a bad_alloc.
    template <class DataType>
    bool Queue<DataType>::isFull() const { 
        return this->canAllocate();
    }
}