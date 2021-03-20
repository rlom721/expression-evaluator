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
        vars.insertToHT("A", "10");
        vars.insertToHT("B", "5");
        vars.insertToHT("C", "-1");
        vars.insertToHT("D", "2");
    }

    // Parametrized constructor sets member variables to arguments 
    Evaluator::Evaluator(string str, string delims) 
        : tknr("", " ()-+/*="), hasFloat(true)  { 
        vars.insertToHT("A", "10");
        vars.insertToHT("B", "5");
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
        string token,                   // current token being processed
               resultKey;               // for variable assignment
        double op1 = 0.0, op2 = 0.0,    // operands for calculation
               result = 0.0;            // final result of expression
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
                // if predefined variable, retrieve its value and push to nums
                // else, define variable to assign result later
                if (isVar(token))
                    nums.push(stod(vars.getValue(token)));
                else {
                    resultKey = token;
                    // vars.insertToHT(resultKey, "EMPTY");
                }
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
            else if (token == "=") {
                result = nums.pop();
                vars.insertToHT(resultKey, to_string(result));
            }
        }

        // final and only item in stack is result
        return result;
    } 

    // This method takes an expression in infix form and returns it as a postfix.
    string Evaluator::infixToPostfix(string expression) { 
        string postfix;
        Stack<string> tempStack;         // for popping to get postfix result
        string token;               // current token
        ParseAction action;         // enum code determines action for a token
        string temp;                // to throw away char "("
        tknr.setStr(expression);    // get tokens

        // loop while there are still tokens to read
        while (tknr.hasNext()) {
            token = tknr.getNextToken();
            action = getAction(token);

            // S1 code means stack input token to s1 stack
            if (action == ParseAction::S1) {
                s1.push(token);
                // postfix += " " + token;
            }
            // S2 code means stack input token to s2 stack
            else if (action == ParseAction::S2) {
                operators.push(token);
            }
            // ERR code means error and invalid input
            else if (action == ParseAction::ERR) {
                cout << "Error! Invalid expression.";
            }
            // unstack operators to s1 until "(" is found then discard "("
            else if (action == ParseAction::UC) {
                while (operators.showTop() != "(") 
                    s1.push(operators.pop());
                temp = operators.pop();
            }
            // unstack operators to s1 until "(" is found
            else if (action == ParseAction::U2) {
                while (!operators.isEmpty())
                    s1.push(operators.pop());
            }
        }

        // unstack operators to s1 until operators is empty
        while (!operators.isEmpty())
            s1.push(operators.pop());
            // postfix += " " + operators.pop();

        // push contents of s1 to a temp stack, then pop to get postfix
        while (!s1.isEmpty())
            tempStack.push(s1.pop());

        while (!tempStack.isEmpty())
            postfix += " " + tempStack.pop();

        return postfix;
    }

    // ADD UNARY CHAR SUPPORT and... constant?
    // This helper function returns a code corresponding to an action based on the current
    // state of member Stack operators. (Implementation based on parse table.)
    // Argument passed is a token from evaluate().
    // add case if token is unary??????
    Evaluator::ParseAction Evaluator::getAction(string token) {
        ParseAction nextAction;     // to return action code

        // input token is a unary operator
        if (isUnaryOp(token)) {
            if (operators.isEmpty()) 
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
            if (operators.isEmpty()) 
                nextAction = ParseAction::S2;
            else 
                nextAction = ParseAction::ERR;
        }
        // input token is + or - operator
        else if (token == "+" || token == "-") {
            if (operators.isEmpty()) 
                nextAction = ParseAction::ERR;
            else if (operators.showTop() == "=" || operators.showTop() == "(") 
                nextAction = ParseAction::S2;
            else if (operators.showTop() == "+" || operators.showTop() == "-" 
                     || operators.showTop() == "*" || operators.showTop() == "/" 
                     || isUnaryOp(operators.showTop()) ) {
                // have to do another comparison
                s1.push(operators.pop());
                nextAction = getAction(token);   // recursive call 
            }
        }
        // input token is * or / operator
        else if (token == "*" || token == "/") {
            if (operators.isEmpty()) 
                nextAction = ParseAction::ERR;
            else if (operators.showTop() == "=" || operators.showTop() == "+" 
                     || operators.showTop() == "-" || operators.showTop() == "(") 
                nextAction = ParseAction::S2;
            else if (operators.showTop() == "*" || operators.showTop() == "/" 
                     || isUnaryOp(operators.showTop()) ) {
                // have to do another comparison
                s1.push(operators.pop());
                nextAction = getAction(token);   // recursive call 
            }
        }
        // input token is ( operator
        else if (token == "(") {
            if (operators.isEmpty()) 
                nextAction = ParseAction::ERR;
            else 
                nextAction = ParseAction::S2;
        }
        // input token is ) operator
        else if (token == ")") {
            if (operators.isEmpty() || operators.showTop() == "=") 
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
        string lowerTk = lowercase(tk);
        
        return lowerTk == "sin" || lowerTk == "cos" || lowerTk == "sqrt" 
               || lowerTk == "abs";
    }

    // returns true if token is a numeric constant
    bool Evaluator::isNum(string token) {
        // check if number - also check negative
        return isdigit(token[0]) || ( token[0] == '-' && isdigit(token[1]) ); 
    }
    
    // EVERTHING BELOW THIS WILL BE DELETED AFTER TESTING
    void Evaluator::showSymTable() {
        vars.GenStatReport();
    }

    // test something...
    void Evaluator::test() {
        
    }
}