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

        // // check if expression is valid first
        // if (!isValidExp(expression))
        //     cout << "Please enter a valid expression.\n";
        // else {
            tknr.setStr(expression);        // to get tokens

            // loop while there are still tokens to get from string
            while (tknr.hasNext()) {
                // nums.showStack();            // FOR DEGUGGING
                token = tknr.getNextToken();

                // token is a constant number (check for negative number too)
                if (isdigit(token[0]) || (token[0] == '-' && isdigit(token[1]))) {
                    nums.push(stod(token));
                }
                // token is a valid variable/identifier (starts with a letter) AND not unary op
                else if (isalpha(token[0]) && !isUnaryOp(token)) {
                    // save name of variable to assign result later
                    if (!firstVarRead) {
                        resultKey = token;
                    }
                    // if predefined variable is operand, push value to nums
                    else if (isVar(token)){
                        nums.push(stod(vars.getValue(token)));
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
                else if (isUnaryOp(token)) {
                    op1 = nums.pop();   // get operand

                    // perform calculation based on operator, push result back to stack
                    if (lowercase(token) == "sin") {
                        nums.push(sin(op1));
                    }
                    else if (lowercase(token) == "cos") {
                        nums.push(cos(op1));
                    }
                    else if (lowercase(token) == "sqrt") {
                        nums.push(sqrt(op1));
                    }
                    else if (lowercase(token) == "abs") {
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
        // }

        // final and only item in stack is result
        return result;
    } 

    // This method takes an expression in infix form and returns it as a postfix.
    string Evaluator::infixToPostfix(string expression) { 
        Stack<string> s1;    // holds operands, then postfix format in reverse
        Stack<string> s2;    // used in getAction and postfix conversion
        string postfix;             // final postfix format
        Stack<string> tempStack;    // for popping to get postfix result
        string token;               // current token
        ParseAction action;         // enum code determines action for a token
        string temp;                // to throw away char "("
        bool compareAgain = false;  // to be used with action U1, comparing same token
        tknr.setStr(expression);    // get tokens

        // loop while there are still tokens to read
        while (tknr.hasNext()) {
            // move on to next token if previous action was NOT U1
            if (!compareAgain) token = tknr.getNextToken();
            action = getAction(token, s2.showTop(), s2.isEmpty());
            compareAgain = false;

            // S1 code means stack input token to s1 stack
            if (action == ParseAction::S1) {
                s1.push(token);
            }
            // S2 code means stack input token to s2 stack
            else if (action == ParseAction::S2) {
                s2.push(token);
            }
            // ERR code means error and invalid input
            else if (action == ParseAction::ERR) {
                cout << "Error! Invalid expression.";
            }
            // UC means unstack s2 to s1 until "(" is found then discard "("
            else if (action == ParseAction::UC) {
                while (s2.showTop() != "(") 
                    s1.push(s2.pop());
                temp = s2.pop();
            }
            // U1 means unstack s2 to s1 then do another comparison
            else if (action == ParseAction::U1) {
                s1.push(s2.pop());
                compareAgain = true;    // don't move to next token
            }
            // U2 means unstack s2 to s1 until "(" is found
            else if (action == ParseAction::U2) {
                while (!s2.isEmpty())
                    s1.push(s2.pop());
            }
        }

        // unstack s2 to s1 until s2 is empty
        while (!s2.isEmpty())
            s1.push(s2.pop());

        // push contents of s1 to a temp stack
        while (!s1.isEmpty())
            tempStack.push(s1.pop());

        // then pop contents to get postfix in correct order
        while (!tempStack.isEmpty())
            postfix += " " + tempStack.pop();

        return postfix;
    }

    // This helper function (used in infix to postfix) returns a code corresponding to an 
    // action based on the current state of s2 stack. (Implementation based on parse table.)
    // Argument passed is a token from evaluate().
    Evaluator::ParseAction Evaluator::getAction(string token, string stackTop, bool stackIsEmpty) {
        ParseAction nextAction;     // to return action code

        // input token is a unary operator
        if (isUnaryOp(token)) {
            if (stackIsEmpty) 
                nextAction = ParseAction::ERR;
            else 
                nextAction = ParseAction::S2;
        }
        // input token is a valid variable name or numeric constant
        else if (isalpha(token[0]) || isNum(token)) {
            nextAction = ParseAction::S1;
        }
        // input token is = operator
        else if (token == "=") {
            if (stackIsEmpty) 
                nextAction = ParseAction::S2;
            else 
                nextAction = ParseAction::ERR;
        }
        // input token is + or - operator
        else if (token == "+" || token == "-") {
            if (stackIsEmpty) 
                nextAction = ParseAction::ERR;
            else if (stackTop == "=" || stackTop == "(") 
                nextAction = ParseAction::S2;
            else if (stackTop == "+" || stackTop == "-" 
                     || stackTop == "*" || stackTop == "/" 
                     || isUnaryOp(stackTop) ) {
                // have to do another comparison
                nextAction = ParseAction::U1;
            }
        }
        // input token is * or / operator
        else if (token == "*" || token == "/") {
            if (stackIsEmpty) 
                nextAction = ParseAction::ERR;
            else if (stackTop == "=" || stackTop == "+" 
                     || stackTop == "-" || stackTop == "(") 
                nextAction = ParseAction::S2;
            else if (stackTop == "*" || stackTop == "/" 
                     || isUnaryOp(stackTop) ) {
                // have to do another comparison
                nextAction = ParseAction::U1;
            }
        }
        // input token is ( operator
        else if (token == "(") {
            if (stackIsEmpty) 
                nextAction = ParseAction::ERR;
            else 
                nextAction = ParseAction::S2;
        }
        // input token is ) operator
        else if (token == ")") {
            if (stackIsEmpty || stackTop == "=") 
                nextAction = ParseAction::ERR;
            else 
                nextAction = ParseAction::UC;
        }
        // input token is empty string or null char
        else if (token == "\0" || token == "") {
            nextAction = ParseAction::U2;
        }

        return nextAction;
    }

    // Helper method converts a string to lowercase char by char
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

    // Search symbol table to determine if token is predefined variable, 
    // then return true if found
    bool Evaluator::isVar(string tk) {
        return vars.findRecord(tk);
    }

    // returns true if operator is sin, cos, sqrt or abs
    bool Evaluator::isUnaryOp(string tk) {
        string lowerTk;
        
        if (isalpha(tk[0])) lowerTk = lowercase(tk);
        
        return lowerTk == "sin" || lowerTk == "cos" || lowerTk == "sqrt" 
               || lowerTk == "abs";
    }

    // returns true if token is a numeric constant
    bool Evaluator::isNum(string token) {
        // check if number - also check negative
        return isdigit(token[0]) || ( token[0] == '-' && isdigit(token[1]) ); 
    }
    
    // returns true if infix expression is valid
    bool isValidExp(std::string expression) {
        bool isValid = false;

        

        return isValid;
    }

    // EVERTHING BELOW THIS WILL BE DELETED AFTER TESTING
    void Evaluator::showSymTable() {
        vars.GenStatReport();
    }
}