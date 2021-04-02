// Implementation file for Parser class
// File name: Parser.cpp

#include "Parser.h"
#include "ParseErr.h"
#include "Stack.h"          // for evaluating postfix expression
#include "Stack.cpp"
#include "List.h"          // for evaluating postfix expression
#include "List.cpp"
#include "ListItem.h"          // for evaluating postfix expression
#include "ListItem.cpp"
#include <iostream>     // for cout
#include <string>
#include <cassert>
using namespace std;
namespace lomboy_a2 {

    // Default constructor sets values to defaults
    Parser::Parser() 
        : str(""), delimiters(" "), ignores(" "), index(0), retDelims(true) { }

    // Parametrized constructor sets member variables to arguments and index to 0
    Parser::Parser(string str, string delims)
        : str(str), delimiters(delims), ignores(" "), index(0), retDelims(true) { }

    // Copy constructor copies member variables
    Parser::Parser(const Parser& tkn) {
        str = tkn.str;
        delimiters = tkn.delimiters;
        ignores = tkn.ignores;
        index = tkn.index;
        retDelims = tkn.retDelims;
    }

    // Sets str member to be tokenized and reset index
    void Parser::setStr(string str) {
        this->str = str;
        reset();
    }

    // Sets delimiters for parsing
    void Parser::setDelims(string delims) {
        delimiters = delims;
    }

    // Sets ignores for parsing tokens
    void Parser::setIgnores(string ignores) {
        this->ignores = ignores;
    }

    // Sets retDelims to true or false
    // If true, getNextToken() method will return delimiters as tokens if found in str.
    void Parser::returnDelims(bool tf) {
        retDelims = tf;
    }            

    // This method takes an expression in infix form and returns it as a postfix.
    string Parser::infixToPostfix(string expression) { 
        Stack<string> s1;    // holds operands, then postfix format in reverse
        Stack<string> s2;    // used in getAction and postfix conversion
        string postfix;             // final postfix format
        Stack<string> tempStack;    // for popping to get postfix result
        string token;               // current token
        ParseAction action;         // enum code determines action for a token
        string temp;                // to throw away char "("
        bool compareAgain = false;  // to be used with action U1, comparing same token
        setStr(expression);         // get tokens

        // loop while there are still tokens to read
        while (hasNext()) {
            // move on to next token if previous action was NOT U1
            if (!compareAgain) token = getNextToken();
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
                postfix = "ERR";
                throw ParseErr();
            }
            // UC means unstack s2 to s1 until "(" is found then discard "("
            // otherwise, stop if not found and show error
            else if (action == ParseAction::UC) {
                while (s2.showTop() != "(" && !s2.isEmpty()) 
                    s1.push(s2.pop());

                if (s2.showTop() == "(") 
                    temp = s2.pop();
                else {
                    postfix = "ERR";
                    throw ParseErr("unmatched parentheses");
                }
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

        if (postfix != "ERR") {
            // unstack s2 to s1 until s2 is empty
            while (!s2.isEmpty())
                s1.push(s2.pop());

            // push contents of s1 to a temp stack
            while (!s1.isEmpty())
                tempStack.push(s1.pop());

            // then pop contents to get postfix in correct order
            while (!tempStack.isEmpty())
                postfix += " " + tempStack.pop();
        }

        return postfix;
    }

    // This helper function (used in infix to postfix) returns a code corresponding to an 
    // action based on the current state of s2 stack. (Implementation based on parse table.)
    // Argument passed is a token from evaluate().
    Parser::ParseAction Parser::getAction(string token, string stackTop, bool stackIsEmpty) {
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

    // Returns following token in str and moves index to next position for future use
    // If retDelims is true, will also return delimiters as tokens if found
    // If char is part of ignores, it will skip them
    // Returns NULL if there is an ignore at the end.
    string Parser::getNextToken() {
        string token = "";                   // to return processed token
        bool endToken = false;             // flag

        // // if index already at end of str OR ignored char at end
        // if (!hasNext() || ( (index == str.length() - 1) && isIgnored(str[index]) ) ) {
        //     cout << "End of string reached. Call reset() to reset index.\n";
        // }

        // check that there are still tokens to read and delimiter not found
        while (hasNext() && !endToken) {

            // if delimiter and set to be tokenized, add to token, increment count and set flag
            // else if not returnDelim, skip (by not ending token)
            if (isDelim(str[index])) {
                // "-" symbol could be negative sign, so check if next char is a number
                if (str[index] == '-' && isdigit(str[index+1])) {
                    token += str[index];
                }
                else if(retDelims && !isIgnored(str[index])) {
                    token += str[index];
                    endToken = true;
                }

                index++;
            }
            // if number, add to token then check if float
            else if (isdigit(str[index])) {
                token += str[index++];

                // if another digit OR decimal, add it to token (and increment index)
                if (str[index] == '.' || isdigit(str[index])) {
                    token += str[index++];
                    while (isdigit(str[index]) && hasNext()) token += str[index++];
                }

                // note: str[index] can be delimiter or string
                endToken = true;  
            }
            // else, is string (potential to check for invalid chars later...)
            else {
                // loop until delimiter found or end reached
                while (!isDelim(str[index]) && hasNext()) token += str[index++];

                endToken = true;
            }
        }

        return token;
    }

    // Resets index to start. To be used if user wants to retiterate through tokens in str.
    void Parser::reset() {
        index = 0;
    }


    // Returns true if there are more characters in string from index position
    bool Parser::hasNext() {
        return index < str.length(); 
    }

    // returns true if operator is sin, cos, sqrt or abs
    bool Parser::isUnaryOp(string tk) {
        string lowerTk;
        
        if (isalpha(tk[0])) lowerTk = lowercase(tk);
        
        return lowerTk == "sin" || lowerTk == "cos" || lowerTk == "sqrt" 
               || lowerTk == "abs";
    }

    // returns true if token is a numeric constant
    bool Parser::isNum(string token) {
        // check if number - also check negative
        return isdigit(token[0]) || ( token[0] == '-' && isdigit(token[1]) ); 
    }

    // Checks if a character is a delimter, returns true if so
    bool Parser::isDelim(char c) {
        return isFound(c, delimiters);
    }

    // Checks if a character is part of ignores, returns true if so
    // ignores should be part of delims (for now!)
    bool Parser::isIgnored(char c) {
        return isFound(c, ignores);
    }


    // Checks if a character is part of a string, returns true if so
    // To be used with isDelim and isIgnored
    bool Parser::isFound(char c, string chars) {
        bool isFound = false;
        size_t i = 0;

        // loop over all chars until match found or end reached
        while (i < chars.length() && !isFound) {
            if (c == chars[i]) isFound = true;
            i++;
        }

        return isFound;
    }

    // Helper method converts a string to lowercase char by char
    string Parser::lowercase(std::string word) {
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
}