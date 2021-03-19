// Program Name:    List, Stack and Queue Stub
// File Name:       main.cpp
// Author:          Rafaela Lomboy
// Date:            2021.03.05
// Description:     This program demonstrates features of the List class, and its
//                  derivatives Stack and Queue classes. It generates stub reports
//                  showing various constructors and methods.

#include <iostream>
#include <string>
// #include <fstream>          // for reading and writing to data files
// #include "List.h"           // testing base class
// #include "List.cpp"           // testing base class
// #include "ListItem.cpp"           // testing base class
// #include "Stack.h"          // testing derived class (parent is List class)
// #include "Stack.cpp"          // testing derived class (parent is List class)
#include <string>
#include "Tokenizer.h"
#include "Evaluator.h"
#include <math.h>
using namespace std;
using namespace lomboy_a2;

// Function prototypes
double evaluate(string expression);
bool isIdentifier(string id);

int main () {
    // // skips WHITESPACE... parsing reqs it...
    // Tokenizer t1;
    // t1.setStr("1 7 3 * + ");
    // t1.setDelims(" ()+-*");
    // t1.setIgnores(" ");

    // cout << "str: " << t1.getStr() 
    //      << "\ndelims: " << t1.getDelims() << endl;

    // for (int i = 0; i < 6; i++) 
    //     cout  << "next token: " << t1.getNextToken() << "\n";
    
    // t1.reset();
    
    // for (int i = 0; i < 3; i++) 
    //     cout  << "next token: " << t1.getNextToken() << "\n";


    Evaluator eval;
    string expression = "5 4 * 3 2 * + 1 -";
    cout << expression << " >> " << eval.evaluate(expression) << endl;
    cout << "1 7 + 5 *" << " >> " << eval.evaluate("1 7 + 5 *") << endl;
    cout << "1 A + 5 *" << " >> " << eval.evaluate("1 A + 5 *") << endl;

    cout << "a - z: " << int('a') << "-" << int('z') << '\n'
         << "A - Z: " << int('A') << "-" << int('Z') << '\n';

    string word = "COS";
    cout << "Converting " << word << " to lower: " 
         << eval.lowercase(word) << endl;
    cout << eval.lowercase("HEY ADORA") << endl;

    cout << "Math: \n" << "|-7| = " << abs(-7)
         << "\nsin(0) = " << sin(0)
         << "\nsqrt(16)) = " << sqrt(16)
         << "\nM_PI = " << M_PI
         << "\nsin(M_PI) = " << sin(M_PI)
         << "\nsin(M_PI/4) = " << sin(M_PI/4) << endl;
    // eval.showStack();
    // eval.test();
    // eval.showStack();

    return 0;
}

// // This method takes a postfix expression and performs the calculation, then returns
// // the result as a double.
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