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
#include <math.h>     // for sin, cos, sqrt, abs functions
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

    // // This method converts an expression from infix to postfix format and returns it.
    // string Evaluator::infixToPostfix(string expression) { 
    //     Stack<string> s1;          // temp holds operands, then final postfix format
    //     string token;               // current token
    //     tknr.setStr(expression);    // get tokens

    //     // loop while there are still tokens to read
    //     while (tknr.hasNext()) {
    //         token = tknr.getNextToken();

    //         // check if valid identifier name, then push to stack
    //         if (isalpha(token[0])) {
    //             // if token NOT in Symbol Table 
    //                 // insert to table
    //             s1.push(token);
    //         }
    //         // if simply a number
    //         else if (isdigit(token[0])) {
    //             s1.push(token);
    //         }
    //         // print error message
    //         else if (getAction(token) == Err) {
    //             cout << "Error! Invalid expression.";
    //         }
    //         // push token to operators stack member
    //         else if (getAction(token) == S2) {
    //             operators.push(token);
    //         }
    //         // // pop operators and push to s1, then compare again
    //         // else if (getAction(token) == U1) {
    //             // << IMPLEMENT WITHIN getAction() >>
    //         // }
    //         else if (getAction(token) == U2) {

    //         }
    //         else if (getAction(token) == Uc) {
            
    //         }
    //     }

    //     // return
    // }

    // This method takes a string in POSTFIX format and calculates then returns the
    // result as a double. 
    // Assumes each parenthesis is paired and symbols are separated by spaces.
    // hmm can be int tho... ADD int or float check? another method tho lol
    double Evaluator::evaluate(string expression) {
        Stack<double> nums;             // initially holds operands, then final result           
        string token;                   // current token being processed
        double op1 = 0.0, op2 = 0.0;    // operands for calculation
        tknr.setStr(expression);        // to get tokens

        // loop while there are still tokens to get from string
        while (tknr.hasNext()) {
            token = tknr.getNextToken();
            // nums.showStack();   // for debugging

            // push operands onto stack (convert to double)
            // OR OPERAND
            if (isdigit(token[0])) {
                nums.push(stod(token));
            }
            // else if (getAction(token) == S1) // identifier {
                // look up action
            // }
            // if operator, perform calculation CHECK SIN, COS...
            // && lowercase(token) != "sin"...) {  // if token not empty CHECK IF OPERATOR!
            else if (token != "\0") {
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
                // else if (lowercase(token) == "sin") {
                //     nums.push(op1 - op2);
                // }
                // add cases for sin , cos, sqrt, abs
            }

        }

        // final and only item in stack is result
        return nums.pop();
    } 

    // bool Evaluator::isOperand(string tk)

    // bool Evaluator::isOperator(string tk)

    // This helper function returns a code corresponding to an action based on the current
    // state of member Stack operators. (Implementation based on parse table.)
    // Argument passed is a token from evaluate().
    Evaluator::ParseAction Evaluator::getAction(string tk) {
        // if (tk.isOperand())
    }

    // Converts a string to lowercase char by char
    string Evaluator::lowercase(std::string word) {
        string lowercase = "";

        for (size_t ch = 0; ch < word.length(); ch++) {
            // check if char is uppercase, then convert by adding (ASCII code difference)
            if (word[ch] >= 'A' && word[ch] <= 'Z')
                lowercase += word[ch] + ('a' - 'A');
            else   
                lowercase += word[ch];
        }

        return lowercase;
    }

    void Evaluator::showStack() {
        cout << operators << endl;
    }

    void Evaluator::test() {
        cout << "Testing Stack member: \n";
        operators.push("Trust");
        operators.push("I");
        operators.push("Men");
    }
}