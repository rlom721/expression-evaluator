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
#include <Tokenizer.h>
// #include <cctype>
// #include <math.h>
using namespace std;
using namespace lomboy_a2;

// Function prototypes
double evaluate(string expression);
bool isIdentifier(string id);

int main () {

    Tokenizer tknzr("Hello world!", " ");

    cout << "str: " << tknzr.getStr() 
         << "\ndelims: " << tknzr.getDelims() 
         << "\nnext token: " << tknzr.getNextToken() 
         << "\nindex: " << int(tknzr.getIndex())
         << "\nnext token: " << tknzr.getNextToken() 
         << "\nindex: " << tknzr.getIndex() << endl;
    
    cout << "Is   a delim? " << (tknzr.isDelim(' ') ? "yes" : "no") << endl;
    cout << "Is @ a delim? " << (tknzr.isDelim('@') ? "yes" : "no") << endl;
    // double A = 2.0, B = 3.0, C = 4.0, D = 5.0;

    // Ask for user input

    // cout << "\nTesting evaluator!\n";
    // parse from infix to postfix!

    // evaluate("A B *");

    return 0;
}



// // This method takes a postfix expression and performs the calculation, then returns
// // the result as a double.
// // Assumes each parenthesis is paired and symbols are separated by spaces.
// double evaluate(string expression) {
//     Stack<double> nums;     // will contain operands, then final result
//     string token = "";      // process tokens from string
//     double result = 0;      // result of operation

//     while (token !=)

//     // if (isIdentifier())

//     return result;
// }

// // Determines if string is a predefined identifier and returns true if so.
// bool isIdentifier(string id) {
//     return (id == "A") || (id == "B") || (id == "C") || (id == "D");
// }