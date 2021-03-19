// Specification file for ListItem class
//
// This ListItem class represents an item (or node) of a linked list.

#ifndef LISTITEM_H
#define LISTITEM_H

#include <iostream>
namespace lomboy_a2 {

    // forward declaration
    template <class DataType> class ListItem;
    template<class DataType> std::ostream& operator<<(std::ostream& out, const ListItem<DataType>& li);

    template <class DataType>
    class ListItem {
    public:
        // typedef
        typedef DataType listDataType;   // type of data/class list item holds
        // constructors
        ListItem();                   // default
        ListItem(listDataType ldt);   // parametrized
        ListItem(listDataType ldt, ListItem* nextItem); // parametrized (may remove...)
        ListItem(const ListItem& li); // copy
        // modification methods
        void set(const listDataType& ldt);
        void setKey(int key);
        // void setKey(const listDataType& ldt);  // no need?
        void setNext(ListItem* nextPtr);
        void setPrev(ListItem* prevPtr);
        ListItem* getNext() { return nextPtr; }
        ListItem* getPrev() { return prevPtr; }        
        // constant methods
        listDataType getData() const { return data; }
        int getKey() const { return key; }
        const ListItem* getNext() const { return nextPtr; }   // cannot change DATA
        const ListItem* getPrev() const { return prevPtr; }  
        // overloaded operators
        ListItem& operator=(const ListItem& li);
        // friend functions
        friend std::ostream& operator<< <DataType>(std::ostream& out, const ListItem<DataType>& li);
    private:
        // member variables
        listDataType data;
        ListItem* nextPtr;
        ListItem* prevPtr;
        int key;
    };

}

#endif
