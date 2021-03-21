// Program Name:    List, Stack and Queue Stub
// File Name:       main.cpp
// Author:          Rafaela Lomboy
// Date:            2021.03.05
// Description:     This program demonstrates features of the List class, and its
//                  derivatives Stack and Queue classes. It generates stub reports
//                  showing various constructors and methods.

#include "Evaluator.h"
// #include "Tokenizer.h"
// #include "Hashtable.h"
#include <iostream>
#include <string>
// #include <math.h>
using namespace std;
using namespace lomboy_a2;

// remove annoying msg in tokenizer end of string reached

int main () {

    Evaluator eval;

    cout << eval.infixToPostfix("y = 7 + 8") << endl;
    cout << eval.infixToPostfix("y = a + b / c * d") << endl;
    cout << eval.infixToPostfix("y = a + 5.0 / 1 * d") << endl;
    cout << eval.infixToPostfix("y = sin( a - b ) / cos (c + d)") << endl;
    cout << "\n y -7 = " << eval.evaluate(" y -7 = ")
         << "\n y 8 y + =" << eval.evaluate(" y 8 y + =")
         << "\n x 9 sqrt =" << eval.evaluate(" x 9 sqrt =");
    // eval.testGetAction();
    // string expression = "x 5 4 * 3 2 * + 1 - =";
    // cout << expression << " >> " << eval.evaluate(expression) << endl;
    // cout << "y A B 1.5 * + C D / - =" << " >> " 
        // << eval.evaluate("y A B 1.5 * + C D / - =") << endl;
    // cout << "w x sqrt =" << " >> " << eval.evaluate("w x sqrt =") << endl;
    // cout << "z x sin =" << " >> " << eval.evaluate("z x sin =") << endl;
    // cout << "v -8.7 =" << " >> " << eval.evaluate("v -8.7 =") << endl;
    // cout << "v -8.7 aBs =" << " >> " << eval.evaluate("v -8.7 aBs =") << endl;
    // cout << "1 A + 5 *" << " >> " << eval.evaluate("1 A + 5 *") << endl;

     // eval.showSymTable();

    return 0;
}