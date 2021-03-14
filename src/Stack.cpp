// Implementation file for Stack class
// File name: Stack.cpp

#include "List.h"        // header file for List class
#include "Stack.h"       // header file for Stack class
#include <iostream>
using namespace std;
namespace lomboy_a2 {

    // Default constructor sets default value of size
    template <class DataType>
    Stack<DataType>::Stack() : size(0) {}

    // Parametrized constructor sets default values of members, then inserts a new
    // entry into list.
    template <class DataType>
    Stack<DataType>::Stack(stackDataType& entry) : size(0) { 
        push(entry);
    }

    // Copy constructor calls base class copy constructor
    template <class DataType>
    Stack<DataType>::Stack(const Stack& s) : List<DataType>(s) {}

    // This method adds an entry to the stack.
    template <class DataType>
    void Stack<DataType>::push(stackDataType entry) {
        // check if stack is full
        if (!this->isFull()) {
            this->insertToHead(entry);
            size = this->getSize();
        }
    }

    // This method pops an entry off the top of the stack and returns it.
    // If stack is empty, prints out error message and returns default value of stack
    // data type.
    template <class DataType>
    typename Stack<DataType>::stackDataType Stack<DataType>::pop() {

        // check if stack is empty
        if (this->isEmpty()) {
            cout << "Cannot pop from empty stack.\n";
            return stackDataType();
        }
        
        typename List<DataType>::iterator topItem = this->start();       // assign iterator to top item
        stackDataType topData = *topItem; // store data of item to return after deletion

        // remove item and update size
        this->removeHead();
        size = this->getSize();

        return topData;
    }

    // This method displays contents of the stack.
    template <class DataType>
    void Stack<DataType>::showStack() {
        this->iterate();
    }

    // This method returns true if stack is empty.
    template <class DataType>
    bool Stack<DataType>::isEmpty() const { 
        return (size == 0); 
    }

    // // This method returns true if there is no space to allocate a new item on stack.
    // // It also throws an exception to indicate a bad_alloc.
    // template <class DataType>
    // bool Stack<DataType>::isFull() const { 
    //     return List<DataType>::isFull();
    // }

    // This method shows the top entry of the stack.
    template <class DataType>
    typename Stack<DataType>::stackDataType Stack<DataType>::showTop() {
        typename List<DataType>::iterator topItem = this->start();       // assign iterator to top item
        stackDataType topData = *topItem; // store data of item to return after deletion

        return topData;
    }
}