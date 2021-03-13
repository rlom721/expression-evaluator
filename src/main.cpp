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
// #include <string>
using namespace std;
using namespace lomboy_a2;

// Function prototypes
void GenListStubReports();          
// void GenStackStubReport();

int main () {
    cout << "TESTING LIST CLASS\n";
    List<int> intList;

    cout << intList;

    intList.insertToHead(7);
    intList.insertToHead(4);
    intList.insertToHead(3);

    cout << intList;

    intList.sortDesc();
    cout << intList;

    List<string> strList;

    strList.insertToTail("K");
    strList.insertToTail("O");
    strList.insertToTail("R");
    strList.insertToTail("R");
    strList.insertToTail("A");

    cout << strList;

    cout << "TESTING STACK CLASS\n";
    Stack<int> intStack;

    cout << intStack;

    intStack.push(7);
    intStack.push(4);
    intStack.push(3);

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

    // generate reports on classes as text files
    GenListStubReports();    // generates two reports (unordered and ordered)
    // GenStackStubReport();    // generates Stack-Stub-Report.txt

    return 0;
}

// This function generates two text files with names "List-Unordered-Report" and
// "List-Ordered-Report" displaying stub program results to demonstrate List class 
// features (constructors and methods).
void GenListStubReports() {
    ofstream outFile1, outFile2;

    // open files
    outFile1.open("List-Unordered-Report.txt");
    outFile2.open("List-Ordered-Report.txt");

    // print out data for Unordered Operations
    outFile1 << "LIST CLASS UNORDERED OPERATIONS REPORT\n\n"
            << "This displays the functionality of the List class, including constructor\n"
            << "use and methods using test data. Only unordered operations shown.\n\n";
    
    // test data
    DataClass dc(0.7), dc1(1.1), dc2(2.4), dc3(3.5);

    List<DataClass> tList(dc), tList1;         // for testing

    outFile1 << "Constructor Tests\n\n";
    outFile1 << "Testing Default constructor...\n";
    outFile1 << "List 2 should have no data.\n";
    outFile1 << tList1 << endl;

    outFile1 << "Testing Parametrized constructor...\n";
    outFile1 << "List 1 initialized with data " << dc << " inserted at start.\n";
    outFile1 << tList;

    outFile1 << "\nMethod Tests\n";
    outFile1 << "Testing insertToHead() method...";
    tList.insertToHead(dc1);
    outFile1 << "\nInserting " << dc1 << " to head...\n";
    outFile1 << tList;

    tList.insertToTail(dc2);
    outFile1 << "\nTesting insertToTail() method...";
    outFile1 << "\nInserting " << dc2 << " to tail...\n";
    outFile1 << tList;

    tList.insertToMid(dc3);
    outFile1 << "\nTesting insertToMid() method...";
    outFile1 << "\nInserting " << dc3 << " to middle...\n";
    outFile1 << tList;

    tList.removeHead();
    outFile1 << "\nTesting removeHead() method...\n";
    outFile1 << "Removed item at head.\n";
    outFile1 << tList;

    tList.removeTail();
    outFile1 << "\nTesting removeTail() method...\n";
    outFile1 << "Removed item at tail\n";
    outFile1 << tList;

    tList.insertToMid(dc);
    outFile1 << "\nInserting " << dc << " to middle...\n";
    outFile1 << tList << endl;

    tList.insertToMid(dc1);
    outFile1 << "\nInserting " << dc1 << " to middle...\n";
    outFile1 << tList;

    tList.remove(4);
    outFile1 << "\nTesting remove() method...\n";
    outFile1 << "Removed item with key 4.\n";
    outFile1 << tList << endl;

    outFile1 << "Testing getSize() method...\n";
    outFile1 << "List size: " << tList.getSize() << endl;

    outFile1 << "\nTesting search() method...\n";

    // look for keys from 0 to 3
    for (int i = 0; i < 4; i++) {
        outFile1 << "Searching for key of " << i << ": "
                << (tList.search(i) ? "found" : "not found") << endl;
    }

    outFile1 << "\nTesting getData() method...\n";
    outFile1 << "Getting item with key 5: " << tList.getData(5) << endl;

    // print out data for Unordered Operations
    outFile2 << "LIST CLASS ORDERED OPERATIONS REPORT\n\n"
            << "This displays the functionality of the List class, including copy constructor\n"
            << "use, iterator and methods using test data. Only ordered operations shown.\n\n";

    List<DataClass> tList2(tList);     // copy contents of first list used above

    outFile2 << "Copy Constructor Test\n\n";
    outFile2 << "Testing Copy constructor...\n";

    outFile2 << "Showing contents of original list:\n";
    outFile2 << tList << endl; 
    outFile2 << "List created with copy constructor:\n";
    outFile2 << tList2;

    outFile2 << "\nTesting sortAsc() method...";
    outFile2 << "\nSorting in ascending order.\n";
    tList2.sortAsc();
    outFile2 << tList2;

    outFile2 << "\nTesting sortDesc() method...";
    outFile2 << "\nSorting in descending order.\n";
    tList2.sortDesc();
    outFile2 << tList2 << endl;

    outFile2 << "Testing isFull method...\n";
    outFile2 << "List is " << (tList2.canAllocate() ? "not full" : "full") << endl;

    outFile2 << "\nList iterator methods tests\n";

    List<DataClass>::iterator iter = tList2.start();

    outFile2 << "\nTesting start() method... (returns iterator to starting item)\n"
             << "List iterator is pointing to start.\n" 
             << "Dereferencing iterator to show data at start: " << *iter << endl;

    outFile2 << "\nTesting hasNext() method...\n"
             << "Is there an item after the current? " 
             << (iter.hasNext() ? "Yes" : "No") << endl;

    outFile2 << "\nTesting iterating over list... (uses hasNext() and overloaded * and ++)\n";

    outFile2 << "START->";
    while (iter.hasNext()) {
        outFile2 << *iter << "->";
        ++iter;
    }
    outFile2 << "END";

    // close files
    outFile1.close();
    outFile2.close();
}

// // This function generates a text file with name "Stack-Stub-Report" displaying 
// // stub program results to demonstrate Stack class features (constructors and methods).
// void GenStackStubReport() {
//     ofstream outFile;

//     outFile.open("Stack-Stub-Report.txt");

//     outFile << "STACK CLASS TEST REPORT\n\n"
//             << "This displays the functionality of the Stack class, including constructor\n"
//             << "use and methods using test data.\n\n";

//     // test data
//     DataClass s0(0.1), s1(0.2), s3(0.3), s4;
//     Stack sTest(s0), sEmpty;

//     outFile << "Constructor Tests\n\n";
//     outFile << "Testing Default constructor...\n";
//     outFile << "Stack should have no data.\n";
//     outFile << sEmpty << endl;

//     outFile << "Testing Parametrized Constructor...\n";
//     outFile << "Stack initialized with data: " << s0 << " inserted.\n";
//     outFile << "Showing Stack Contents:\n";
//     outFile << sTest << endl;

//     Stack sTest2(sTest);
//     outFile << "Testing Copy constructor...\n";
//     outFile << "Showing contents of original stack:\n";
//     outFile << sTest; 
//     outFile << "Stack created with copy constructor:\n";
//     outFile << sTest2 << endl;

//     outFile << "Methods Tests\n\n";
//     outFile << "Testing push() method...\n";
//     sTest.push(s1);
//     outFile << sTest << endl;

//     outFile << "Testing showTop() method...\n";
//     outFile << "Data at top: " << sTest.showTop() << endl;

//     outFile << "Testing pop() method...\n";
//     s4 = sTest.pop();
//     outFile << sTest << endl;

//     outFile << "Popped data " << s4 << " off stack!\n";

//     outFile << "\nTesting isEmpty() method...\n";
//     outFile << "Stack is " << (sTest.isEmpty() ? "empty" : "not empty") << endl;

//     outFile << "\nTesting isFull method...\n";
//     outFile << "Stack is " << (sTest.canAllocate() ? "not full" : "full") << endl;

//     outFile.close();
// }