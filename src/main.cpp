// Program Name:    List, Stack and Queue Stub
// File Name:       main.cpp
// Author:          Rafaela Lomboy
// Date:            2021.03.05
// Description:     This program demonstrates features of the List class, and its
//                  derivatives Stack and Queue classes. It generates stub reports
//                  showing various constructors and methods.

#include <iostream>
#include <fstream>          // for reading and writing to data files
#include "List.h"           // testing base class
#include "List.cpp"           // testing base class
#include "ListItem.cpp"           // testing base class
#include "Stack.h"          // testing derived class (parent is List class)
#include "Stack.cpp"          // testing derived class (parent is List class)
#include "DataClass.h"      // for producing test data
#include <string>
using namespace std;
using namespace lomboy_a2;

// Function prototypes

int main () {
    cout << "TESTING LIST CLASS\n";
    List<string> strList;

    strList.insertToTail("K");
    strList.insertToTail("O");
    strList.insertToTail("R");
    strList.insertToTail("R");
    strList.insertToTail("A");

    cout << strList;
    cout << "List " << (strList.isFull() ? "is full": "is not full") << endl;

    cout << "TESTING STACK CLASS\n";
    Stack<int> intStack;

    intStack.push(7);
    intStack.push(4);
    intStack.push(3);

    cout << "Stack " << (intStack.isFull() ? "is full": "is not full") << endl;
    cout << intStack;

    cout << "Popping off stack!\n";
    // cout << intStack.pop();
    cout << intStack.pop() << endl 
         << intStack.pop() << endl
         << intStack.pop() << endl
         << intStack.pop() << endl
         << intStack.pop() << endl;

    cout << intStack;

    intStack.sortDesc();
    cout << intStack;
    
    Stack<char> strStack;

    strStack.push('K');
    strStack.push('O');
    strStack.push('R');
    strStack.push('R');
    strStack.push('A');

    cout << strStack;

    cout << "Popping letters off:\n";

    while (!strStack.isEmpty())
        cout << strStack.pop() << endl;

    cout << strStack;

    return 0;
}