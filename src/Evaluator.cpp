// Implementation file for Evaluator class
// File name: Evaluator.cpp

#include "Evaluator.h"
#include "Parser.h"
#include "Stack.h"          // for evaluating postfix expression
#include "Stack.cpp"
#include "List.h"          // for evaluating postfix expression
#include "List.cpp"
#include "ListItem.h"          // for evaluating postfix expression
#include "ListItem.cpp"
#include <string>
#include <iostream>     // for cout
#include <math.h>     // for sin, cos, sqrt, abs functions
// #include <exception>     // for throwing exceptions
// #include <cassert>
using namespace std;
namespace lomboy_a2 {

    // Default constructor sets values to defaults (such as delimiters for Parser)
    // and inserts predefined variable values into symbol table
    Evaluator::Evaluator() : tknr("", " ()-+/*=") { 
        vars.insertToHT("A", "10");
        vars.insertToHT("B", "5");
        vars.insertToHT("C", "-1");
        vars.insertToHT("D", "2");
    }

    // Parametrized constructor sets member variables to arguments 
    Evaluator::Evaluator(string str, string delims) 
        : tknr("", " ()-+/*=") { 
        vars.insertToHT("A", "10");
        vars.insertToHT("B", "5");
        vars.insertToHT("C", "-1");
        vars.insertToHT("D", "2");
    }

    // Copy constructor copies member variables
    Evaluator::Evaluator(const Evaluator& eval) {
        tknr = eval.tknr;
        // operators = eval.operators;
        vars.insertToHT("A", "5");
        vars.insertToHT("B", "10");
        vars.insertToHT("C", "-1");
        vars.insertToHT("D", "2");
    }

    // This method takes a string in postfix format and calculates then returns the
    // result as a double. 
    // Assumes each parenthesis is paired and symbols are separated by spaces.
    double Evaluator::evaluate(string expression) {
        Stack<double> nums;             // initially holds operands, then final result           
        string token,                   // current token being processed
               resultKey;               // for variable assignment
        double op1 = 0.0, op2 = 0.0,    // operands for calculation
               result = 0.0;            // final result of expression
        bool firstVarRead = false;      // has first variable been read?

        tknr.setStr(expression);        // to get tokens

        // loop while there are still tokens to get from string
        while (tknr.hasNext()) {
            // nums.showStack();            // FOR DEGUGGING
            token = tknr.getNextToken();

            // check for valid identifier name on left-hand side
            if (!firstVarRead && !isalpha(token[0])) {
                throw runtime_error("invalid identifier on left-hand side");
            }
            // token is a constant number (check for negative number too)
            else if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
                nums.push(stod(token));
            }
            // token is a valid variable/identifier (starts with a letter) AND not unary op
            else if (isalpha(token[0]) && !tknr.isUnaryOp(token)) {
                // save name of variable to assign result later
                if (!firstVarRead) {
                    resultKey = token;
                }
                // if predefined variable is operand, push value to nums
                else if (isVar(token)){
                    nums.push(stod(vars.getValue(token)));
                }
                // invalid variable provided (not predefined and on right-hand side)
                else {
                    throw runtime_error("undefined identifier(s) on right-hand side");
                }

                firstVarRead = true;
            }
            // if binary operator, perform calculation
            else if (token == "*" || token == "/" || token == "+" || token == "-") {
                op2 = nums.pop();   // get operands
                op1 = nums.pop();

                // perform calculation based on operator, push result back to stack
                if (token == "*") {
                    nums.push(op1 * op2);
                }
                else if (token == "/") {
                    if (op2 == 0)
                        throw runtime_error("division by zero");
                    else
                        nums.push(op1 / op2);
                }
                else if (token == "+") {
                    nums.push(op1 + op2);
                }
                else if (token == "-") {
                    nums.push(op1 - op2);
                }
            }
            // if unary op, perform calculation (also check its not empty or string with null)
            else if (tknr.isUnaryOp(token)) {
                op1 = nums.pop();   // get operand

                // perform calculation based on operator, push result back to stack
                if (tknr.lowercase(token) == "sin") {
                    nums.push(sin(op1));
                }
                else if (tknr.lowercase(token) == "cos") {
                    nums.push(cos(op1));
                }
                else if (tknr.lowercase(token) == "sqrt") {
                    nums.push(sqrt(op1));
                }
                else if (tknr.lowercase(token) == "abs") {
                    nums.push(abs(op1));
                }
            }
            // if assignment operator, then pop result from stack and assign to variable
            // used as resultKey (the first identifier encountered)
            else if (token == "=" ) {
                result = nums.pop();
                vars.insertToHT(resultKey, to_string(result));
            }
        }

        // final and only item in stack is result
        return result;
    } 

    // Search symbol table to determine if token is predefined variable, 
    // then return true if found
    bool Evaluator::isVar(string tk) {
        return vars.findRecord(tk);
    }

    // EVERTHING BELOW THIS WILL BE DELETED AFTER TESTING
    void Evaluator::showSymTable() {
        vars.GenStatReport();
    }
}