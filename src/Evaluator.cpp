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
    Evaluator::Evaluator() : tknr("", " ()-+/*="), hasFloat(true) { }

    // Parametrized constructor sets member variables to arguments 
    Evaluator::Evaluator(string str, string delims) 
        : tknr("", " ()-+/*="), hasFloat(true)  { }

    // Copy constructor copies member variables
    Evaluator::Evaluator(const Evaluator& eval) {
        tknr = eval.tknr;
        hasFloat = eval.hasFloat;
    }

    // This method takes a string in POSTFIX format and calculates then returns the
    // result as a double. 
    // Assumes each parenthesis is paired and symbols are separated by spaces.
    // hmm can be int tho... ADD int or float check? another method tho lol
    double Evaluator::evaluate(std::string expression) {
        Stack<double> nums;             // initially holds operands, then final result           
        string token;                   // current token being processed
        double op1 = 0.0, op2 = 0.0;    // operands for calculation
        tknr.setStr(expression);        // to get tokens

        // loop while there are still tokens to get from string
        while (tknr.hasNext()) {
            token = tknr.getNextToken();
            // nums.showStack();   // for debugging

            // push operands onto stack (convert to double)
            if (isdigit(token[0])) 
                nums.push(stod(token));
            // if operator, perform calculation
            else if (token != "\0") {  // if token not empty CHECK IF OPERATOR!
                op2 = nums.pop();   // get operands
                op1 = nums.pop();

                // perform calculation based on operator, push result back to stack
                if (token == "*") {
                    nums.push(op1 * op2);
                }
                else if (token == "/") {
                    nums.push(op1 / op2);
                }
                else if (token == "+") {
                    nums.push(op1 + op2);
                }
                else if (token == "-") {
                    nums.push(op1 - op2);
                }
                // add cases for sin , cos, sqrt, abs
            }
        }

        // final and only item in stack is result
        return nums.pop();
    } 

    // bool Evaluator::isOperator(string operator)
}