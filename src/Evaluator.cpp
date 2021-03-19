// Implementation file for Evaluator class
// File name: Evaluator.cpp

#include "Evaluator.h"
// #include "Hashtable.h"
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
    // and inserts predefined variable values into symbol table
    Evaluator::Evaluator() : tknr("", " ()-+/*="), hasFloat(true) { 
        vars.insertToHT("A", "5");
        vars.insertToHT("B", "10");
        vars.insertToHT("C", "-1");
        vars.insertToHT("D", "2");
    }

    // Parametrized constructor sets member variables to arguments 
    Evaluator::Evaluator(string str, string delims) 
        : tknr("", " ()-+/*="), hasFloat(true)  { 
        vars.insertToHT("A", "5");
        vars.insertToHT("B", "10");
        vars.insertToHT("C", "-1");
        vars.insertToHT("D", "2");
    }

    // Copy constructor copies member variables
    Evaluator::Evaluator(const Evaluator& eval) {
        tknr = eval.tknr;
        hasFloat = eval.hasFloat;
        operators = eval.operators;
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
        string token;                   // current token being processed
        double op1 = 0.0, op2 = 0.0;    // operands for calculation
        tknr.setStr(expression);        // to get tokens

        // loop while there are still tokens to get from string
        while (tknr.hasNext()) {
            token = tknr.getNextToken();

            // number is a 
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

    // This method takes an expression in infix form and returns it as a postfix.
    string Evaluator::infixToPostfix(string expression) { 
        string token;               // current token
        tknr.setStr(expression);    // get tokens

        // loop while there are still tokens to read
        while (tknr.hasNext()) {
            token = tknr.getNextToken();

            // if simply a constant number
            if (isdigit(token[0])) {
                s1.push(token);
            }
            // check if unary operator name !!! CHECK LOGIC
            else if (lowercase(token) == "sin" || lowercase(token) == "cos" 
                     || lowercase(token) == "sqrt" || lowercase(token) == "abs") {
                s1.push(token);
            }
            // check if valid identifier name, then push to stack
            else if (isalpha(token[0]) ) { // check in getAction instead?
                // if token NOT in Symbol Table, insert it ! FIX for personal var assn
                // if (!isOperand(token)) vars.insertToHT(token, ???);
                s1.push(token);
            }
            // print error message
            else if (getAction(token) == ParseAction::ERR) {
                cout << "Error! Invalid expression.";
            }
            // push token to operators stack member
            else if (getAction(token) == ParseAction::S2) {
                operators.push(token);
            }
            // // pop operators and push to s1, then compare again
            // else if (getAction(token) == U1) {
                // << IMPLEMENT WITHIN getAction() >>
            // }
            // unstack operators to s1 until "(" is found then discard "("
            else if (getAction(token) == ParseAction::U2) {
                // while ()
            }
            // unstack operators to s1 until operators is empty
            else if (getAction(token) == ParseAction::UC) {
            
            }
        }

        // return
    }

    bool Evaluator::isOperand(string tk) {
        return vars.findRecord(tk);
    }

    // bool Evaluator::isOperator(string tk)

    // This helper function returns a code corresponding to an action based on the current
    // state of member Stack operators. (Implementation based on parse table.)
    // Argument passed is a token from evaluate().
    // add case if token is unary??????
    Evaluator::ParseAction Evaluator::getAction(string token) {
        ParseAction nextAction;     // to return action code

        // token is operand (column <identifier>)
        if (isOperand(token)) {
            nextAction = ParseAction::S1;
        }
        // token is = operator
        else if (token == "=") {
            if (operators.isEmpty()) nextAction = ParseAction::S2;
            else nextAction = ParseAction::ERR;
        }
        // token is + or - operator
        else if (token == "+" || token == "-") {
            if (operators.isEmpty()) 
                nextAction = ParseAction::ERR;
            else if (operators.showTop() == "=" || operators.showTop() == "(") 
                nextAction = ParseAction::S2;
            else if (operators.showTop() == "+" || operators.showTop() == "-"
                     || operators.showTop() == "*" || operators.showTop() == "/") {
                // have to do another comparison
                s1.push(operators.pop());
                getAction(token);   // recursive call 
            }
        }
        // token is * or / operator
        else if (token == "*" || token == "/") {
            if (operators.isEmpty()) 
                nextAction = ParseAction::ERR;
            else if (operators.showTop() == "=" || operators.showTop() == "+" 
                     || operators.showTop() == "-" || operators.showTop() == "(") 
                nextAction = ParseAction::S2;
            else if (operators.showTop() == "*" || operators.showTop() == "/") {
                // have to do another comparison
                s1.push(operators.pop());
                getAction(token);   // recursive call 
            }
        }
        // token is ( operator
        else if (token == "(") {
            if (operators.isEmpty()) nextAction = ParseAction::ERR;
            else nextAction = ParseAction::S2;
        }
        // token is ) operator
        else if (token == ")") {
            if (operators.isEmpty() || operators.showTop() == "=") 
                nextAction = ParseAction::ERR;
            else nextAction = ParseAction::UC;
        }
        // token is empty string or null char
        else if (token == "\0" || token == "") {
            nextAction = ParseAction::U2;
        }

        return nextAction;
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

    // EVERTHING BELOW THIS WILL BE DELETED AFTER TESTING
    void Evaluator::showSymTable() {
        vars.GenStatReport();
    }
}