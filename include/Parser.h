// Specification file for Parser class
//
// This class takes a string and provides methods for tokenizing it.
// It also provides a method for converting from infix to postfix.

#ifndef PARSER_H
#define PARSER_H

#include "Stack.h"          // for evaluating postfix expression
#include "Queue.h"          
#include <string>
namespace lomboy_a2 {

    class Parser {
    public:
        // Constructors
        Parser();
        Parser(std::string str, std::string delims);
        Parser(const Parser& tkn);
        // Modification methods
        std::string infixToPostfix(std::string expression);
        void setStr(std::string str);
        void setDelims(std::string delims);
        void setIgnores(std::string ignores);
        void returnDelims(bool tf);             // sets retDelim
        std::string getNextToken();
        void DoU1();
        void DoU2();
        void DoUC();
        void DoS1(std::string tk);
        void DoS2(std::string tk);
        // Constant methods
        bool hasNext();
        std::string getStr() { return str; }
        std::string getDelims() { return delimiters; }
        std::string getIgnores() { return ignores; }
        bool isUnaryOp(std::string tk);     
        bool isNum(std::string tk);      
        bool isFound(char c, std::string chars); 
        std::string lowercase(std::string word);
    private:
        // enum - action codes for converting to postfix
        enum class ParseAction { S1, S2, ERR, U1, U2, UC };
        // Helper functions
        ParseAction getAction(std::string tk, std::string stackTop, bool stackIsEmpty);
        bool isDelim(char c); 
        bool isIgnored(char c); 
        // Member variables
        Queue<std::string> s1;    // holds operands, then postfix format in reverse
        Stack<std::string> s2;    // used in getAction and postfix conversion
        std::string str;
        std::string delimiters;
        std::string ignores;
        size_t index;          // keeps track of current string position
        bool retDelims;        // getNextToken will return delimiters
    };

}

#endif