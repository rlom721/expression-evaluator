// Specification file for Evaluator class
//
// This class provides methods for converting an expression from infix to 
// postfix and evaluating it.

#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Hashtable.h"
#include "Parser.h"
// #include "Stack.h"          // for evaluating postfix expression
#include <string>
namespace lomboy_a2 {

    class Evaluator {
        // typedef
        typedef Hashtable SymbolTable;
    public:
        // Constructors
        Evaluator();
        Evaluator(std::string str, std::string delims);
        Evaluator(const Evaluator& tkn);    // copy
        // Modification methods
        double evaluate(std::string expression);  // hmm can be int tho...
        // void reset();
        // Constant methods
        // std::string infixToPostfix(std::string expression);
        void showSymTable();
        // bool isOperand(string tk);
    private:
        // enum - action codes for converting to postfix
        // enum class ParseAction { S1, S2, ERR, U1, U2, UC };
        // Helper functions
        // ParseAction getAction(std::string tk, std::string stackTop, bool stackIsEmpty);
        bool isVar(string tk);    // SymbolTable lookup
        bool isValidExp(std::string expression);
        // Member variables
        Parser tknr;         // used to parse out tokens
        SymbolTable vars;    // stores variables and data
    };

}

#endif