// Program Name:    Expression Evaluator
// File Name:       main.cpp
// Author:          Rafaela Lomboy
// Date:            2021.03.26
// Description:     This program...

#include "Evaluator.h"
// #include "Tokenizer.h"
#include <iostream>
#include <string>
#include <limits>       // for cin.ignore()
// #include <math.h>
using namespace std;
using namespace lomboy_a2;

// ADD CHECK IF VAR IS NOT ON LHS
// add check if NOT EXPRESSION!
// remove annoying msg in tokenizer end of string reached
// fix copy - hashtable contents

int main () {
    Evaluator eval;         // used to evaluate math expressions
    string expression,      // user-inputted infix expression
           postfix,         // converted to postfix format
           lhsVar;          // left-hand side variable
    bool done = false;      // program loop flag
    char answer;            // user chooses to quit or continue

    cout << "Welcome to the Expression Evaluator!\n"
         << "This program evaluates expressions written in infix format (ex. y = a + (b * c)).\n"
         << "It supports addition, subtraction, divison, multiplication operators and\n"
         << "the following unary operators: sin, cos, abs (absolute value) and sqrt (square \n"
         << "root). It also supports user-defined variables.\n"
         << "The following variables have been predefined: \n"
         << "A = 10, B = 5, C = -1, D = 2\n\n";

    while (!done) {
        cout << "Enter an expression: ";
        getline(cin, expression);

        cout << "You entered: " << expression << endl;

        // convert expression to postfix, then evaluate and display result
        postfix = eval.infixToPostfix(expression);
        lhsVar = expression.substr(0, expression.find('='));
        cout << lhsVar << "= " << eval.evaluate(postfix) << endl;
        // cout << eval.evaluate(eval.infixToPostfix("y = 7 + 8")) << endl;
        // cout << eval.infixToPostfix("y = a + b / c * d") << endl;
        // cout << eval.infixToPostfix("y = a + 5.0 / 1 * d") << endl;
        // cout << eval.infixToPostfix("y = sin( a - b ) / cos (c + d)") << endl;

        cout << "Would you like to enter another expression?\nEnter q to quit or any key to continue: ";
        cin.get(answer);

        // clear buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // loop control
        if (answer == 'q' || answer == 'Q') done = true;
    }
    // eval.showSymTable();

    cout << "Ending Expression Evaluator program... Goodbye!\n";

    return 0;
}