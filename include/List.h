// Specification file for List class
//
// This List class is a linked list with methods to insert, sort, search, iterate
// through list.

#ifndef LIST_H
#define LIST_H

#include "ListItem.h"    // header file for ListItem class
#include <iostream>
namespace lomboy_a2 {

    // forward declarations
    template <class DataType> class List;
    template <class DataType> std::ostream& operator<<(std::ostream& out, const List<DataType>& l);
    template <class DataType> 
    bool operator!=(const typename List<DataType>::iterator& it1, const typename List<DataType>::iterator& it2);
    template <class DataType> 
    bool operator==(const typename List<DataType>::iterator& it1, const typename List<DataType>::iterator& it2);

    template <class DataType>
    class List {
    public:
        // forward declaration
        class iterator;
        // typedef
        typedef DataType listDataType; 
        typedef ListItem<DataType> listItemType;
        // Constructors
        List();
        List(listDataType data);
        List(const List& l);    // use deep copy - do NOT copy pointers!
        // Destructor
        ~List();
        // Modification methods
        void insertToHead(const listDataType& entry);
        void insertToTail(const listDataType& entry);
        void insertToMid(const listDataType& entry);
        void remove(int key);
        void removeHead();
        void removeTail();
        bool search(int key);
        void sortAsc();            // uses selection sort
        void sortDesc();
        void iterate();            // displays list contents to console as linked list!
        bool isEmpty() { return (size == 0); }         
        // Constant methods
        iterator start() const; 
        iterator end() const;
        listDataType getData(int key);
        bool isFull() const;
        int getSize() const { return size; };
        // Friend functions and classes
        friend std::ostream& operator<< <DataType>(std::ostream& out, const List<DataType>& l);
        // Nested class (is also implicitly a friend)
        class iterator {
            // friend classes/classes
            friend class List;
            // typedef
            typedef listItemType itemType;  // iterator points to this type
            typedef List<DataType>::listDataType itemData;  // iterator points to this type
        public:
            // Constructors
            iterator();
            iterator(itemType* start);
            iterator(const iterator& it);
            // Modification methods
            itemData getNext();
            // Constant methods
            bool hasNext() const;
            itemData operator*() const;
            // Overloaded operators
            iterator& operator=(const iterator& it);
            iterator& operator++();     // prefix increment
            iterator& operator--();     // prefix decrement
            // Friend functions
            friend bool operator!= <DataType>(const iterator& it1, const iterator& it2);
            friend bool operator== <DataType>(const iterator& it1, const iterator& it2);
        private:
            const itemType* currentPtr;
            int itemNum;
        };
    private:
        // Helper functions
        void clearList();
        listItemType* find(int key);
        void swapItems(listItemType& li1, listItemType& li2);
        void insertCopy(const listDataType& entry);
        // Member variables
        listItemType* headPtr;
        listItemType* tailPtr;
        int size;
        int keyMkr;             // generate a unique key for list item
    };

}

#endif
