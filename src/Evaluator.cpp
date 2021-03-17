// Implementation file for Evaluator class
// File name: Evaluator.cpp

#include "Evaluator.h"
// #include "SymbolTable.h"
#include "Tokenizer.h"
#include "Stack.h"          // for evaluating postfix expression
#include "Stack.cpp"
#include "List.h"          // for evaluating postfix expression
#include "List.cpp"
#include "ListItem.h"          // for evaluating postfix expression
#include "ListItem.cpp"
#include <string>
#include <iostream>     // for cout
// #include <cassert>
using namespace std;
namespace lomboy_a2 {

    // Default constructor sets values to defaults (such as delimiters for tokenizer)
    Evaluator::Evaluator() : tknr("", " ()-+/*"), hasFloat(true) { }

    // Parametrized constructor sets member variables to arguments 
    Evaluator::Evaluator(string str, string delims) 
        : tknr("", " ()-+/*"), hasFloat(true)  { }

    // Copy constructor copies member variables
    Evaluator::Evaluator(const Evaluator& eval) {
        tknr = eval.tknr;
        hasFloat = eval.hasFloat;
    }

    // CURRENTLY only separates tokens into stacks!
    // This method takes a string in POSTFIX format and calculates then returns the
    // result as a double. 
    // hmm can be int tho... ADD int or float check? another method tho lol
    double Evaluator::evaluate(std::string expression) {
        Stack<int> S1;
        Stack<string> S2;
        double result = 0;
        string currentToken;
        tknr.setStr(expression);        // to get tokens

        // tokenize string, process each token one by one
        while (tknr.hasNext()) {
            currentToken = tknr.getNextToken();
            if (isdigit(currentToken[0])) 
                S1.push(stod(currentToken));
            else if (currentToken != "") // if operator
                S2.push(currentToken);
        }

        cout << "S1 stack:\n";
        S1.showStack();
        cout << "S2 stack:\n";
        S2.showStack();

        return result;
    } 
}