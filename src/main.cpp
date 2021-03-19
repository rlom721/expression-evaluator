// Program Name:    List, Stack and Queue Stub
// File Name:       main.cpp
// Author:          Rafaela Lomboy
// Date:            2021.03.05
// Description:     This program demonstrates features of the List class, and its
//                  derivatives Stack and Queue classes. It generates stub reports
//                  showing various constructors and methods.

#include "Evaluator.h"
#include "Tokenizer.h"
#include "Hashtable.h"
#include <iostream>
#include <string>
#include <math.h>
using namespace std;
using namespace lomboy_a2;

int main () {
    Evaluator eval;
    string expression = "5 4 * 3 2 * + 1 -";
    cout << expression << " >> " << eval.evaluate(expression) << endl;
    cout << "1 7 + 5 *" << " >> " << eval.evaluate("1 7 + 5 *") << endl;
    cout << "1 A + 5 *" << " >> " << eval.evaluate("1 A + 5 *") << endl;

     // eval.showSymTable();

    return 0;
}