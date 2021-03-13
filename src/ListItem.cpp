// Implementation file for ListItem class
// File name: ListItem.cpp

#include "ListItem.h"    // header file for ListItem class
#include <iostream>
using namespace std;
namespace lomboy_a2 {

    // Default constructor uses default constructor of listDataType to set default value
    // for data field, then sets nextPtr field to nullptr
    template <class DataType>
    ListItem<DataType>::ListItem()
        : data(listDataType()), nextPtr(nullptr), prevPtr(nullptr), key(0) { }

    // Parametrized constructor takes argument of listDataType and sets data field to it,
    // then sets nextPtr and prevPtr fields to nullptr
    template <class DataType>
    ListItem<DataType>::ListItem(listDataType ldt)
        : data(ldt), nextPtr(nullptr), prevPtr(nullptr), key(0) { }

    // Parametrized constructor sets data and nextPtr fields to arguments then sets prevPtr
    // pointer to nullptr.
    template <class DataType>
    ListItem<DataType>::ListItem(listDataType ldt, ListItem* nextItem)
        : data(ldt), nextPtr(nextItem), prevPtr(nullptr), key(0) { }

    // Copy constructor copies data value (and key via copy assignment) from another 
    // ListItem, but NOT its pointers! It sets nextPtr and prevPtr fields to nullptr
    template <class DataType>
    ListItem<DataType>::ListItem(const ListItem& li) {
        data = li.getData();
        nextPtr = nullptr;
        prevPtr = nullptr;
        key = li.key;
    }

    // This method sets the data AND key field to the argument provided (via
    // copy assignment).
    template <class DataType>
    void ListItem<DataType>::set(const listDataType& ldt) {
        data = ldt;
    }

    // This method sets only the key field of the data.
    template <class DataType>
    void ListItem<DataType>::setKey(int key) {
        this->key = key;
    }

    // This method sets nextPtr field (pointer to next ListItem) to the argument provided.
    template <class DataType>
    void ListItem<DataType>::setNext(ListItem* nextPtr) {
        this->nextPtr = nextPtr;
    }

    // This method sets prevPtr field (pointer to previous ListItem) to argument provided.
    template <class DataType>
    void ListItem<DataType>::setPrev(ListItem* prevPtr) {
        this->prevPtr = prevPtr;
    }

    // Overloaded copy assignment
    // This method copies data value from another ListItem object, but NOT its pointers!
    template <class DataType>
    ListItem<DataType>& ListItem<DataType>::operator=(const ListItem& li) {
        // check for self-assignment
        if (this != &li) {
            data = li.getData();
        }

        return *this;
    }

    // Friend function: Overloaded outstream operator
    // Displays data of ListItem object
    // Assumes listDataType can be outputted to console (or has outstream capabilities) and
    // that listDataType has getData member function.
    template <class DataType>
    ostream& operator<<(ostream& out, const ListItem<DataType>& li){
        out << li.getData() << " (" << li.getDataKey() << ")" << endl;

        // check for nullptr to avoid seg fault
        if (li.nextPtr == nullptr)
            out << "nextPtr is nullptr";
        else
            out << "nextPtr " << li.nextPtr->getData();

        if (li.prevPtr == nullptr)
            out << "\nprevPtr is nullptr" << endl;
        else
            out << "\nprevPtr " << li.prevPtr->getData() << endl;

        return out;
    }

}
