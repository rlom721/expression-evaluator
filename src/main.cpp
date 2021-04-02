// Program Name:    Expression Evaluator
// File Name:       main.cpp
// Author:          Rafaela Lomboy
// Date:            2021.03.26
// Description:     This program...

#include "Evaluator.h"
#include "Parser.h"
#include "ParseErr.h"
#include <iostream>
#include <string>
#include <limits>       // for cin.ignore()
using namespace std;
using namespace lomboy_a2;

int main () {
    Evaluator eval;         // used to evaluate math expressions
    Parser prsr("", " ()-+/*=");  // used to convert to postfix (arguments: expression, delimiters)
    string expression,      // user-inputted infix expression
           postfix,         // converted to postfix format
           lhsVar;          // left-hand side variable
    double result = 0.0;    // result of entered expression
    bool done = false;      // program loop flag
    char answer;            // user chooses to quit or continue

    cout << "Welcome to the Expression Evaluator!\n"
         << " This program evaluates expressions written in infix format.\n"
         << " It supports addition, subtraction, divison, multiplication operators and\n"
         << " the following unary operators: sin, cos, abs (absolute value) and sqrt (square \n"
         << " root). It also supports user-defined variables.\n"
         << "IMPORTANT:\n -use of unary operators require parentheses (ex. sin(x)).\n"
         << " -user-defined variables are case-sensitive (e.g. lambda is NOT equal to LAMBDA)\n\n"
         << "The following variables have been predefined: \n"
         << "A = 10, B = 5, C = -1, D = 2\n\n";

    while (!done) {
        cout << "Enter an expression: ";
        getline(cin, expression);

        // convert expression to postfix, then evaluate and display result
        try {
            // convert from infix to postfix then display
            postfix = prsr.infixToPostfix(expression);
            cout << "Postfix: " << postfix << endl;

            // evaluate result then display left-hand variable equal to result
            result = eval.evaluate(postfix);
            lhsVar = expression.substr(0, expression.find('='));
            cout << lhsVar << "= " << result << endl;
        }
        // check for evaluation error
        catch (runtime_error& re) {
            cerr << "Evaluator Error - " << re.what() << "." << endl;
        }
        // check for parse error thrown
        catch (ParseErr& pe) {
            cerr << "Parse Error - " << pe.what() << endl;
        }

        // cout << eval.evaluate(eval.infixToPostfix("y = 7 + 8")) << endl;
        // cout << eval.infixToPostfix("y = a + b / c * d") << endl;
        // cout << eval.infixToPostfix("y = a + 5.0 / 1 * d") << endl;
        // cout << eval.infixToPostfix("y = sin( a - b ) / cos (c + d)") << endl;

        cout << "\nWould you like to enter another expression?\nEnter q to quit or any key to continue: ";
        cin.get(answer);

        // clear buffer
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        // loop control
        if (answer == 'q' || answer == 'Q') done = true;
    }
    
    cout << "Ending Expression Evaluator program... Goodbye!\n";

    return 0;
}