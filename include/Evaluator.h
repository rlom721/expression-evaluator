// Specification file for Evaluator class
//
// This class provides methods for converting an expression from infix to 
// postfix and evaluating it.

#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Hashtable.h"
#include "Tokenizer.h"
#include "Stack.h"          // for evaluating postfix expression
#include <string>
namespace lomboy_a2 {

    // return MOST PRECISE... so int or float? how tho...

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
        bool isOperand(string tk);
        void showSymTable();

        std::string lowercase(std::string word);
        void test();            // testing
        std::string infixToPostfix(std::string expression);
    private:
        // enum - action codes for converting to postfix
        enum class ParseAction { S1, S2, ERR, U1, U2, UC };
        // Helper functions
        ParseAction getAction(std::string tk);
        bool isIdentifier();    // SymbolTable lookup
        bool isBinaryOp();      // SymbolTable lookup
        // Member variables
        Tokenizer tknr;
        Stack<std::string> operators;
        SymbolTable vars;    // stores variables and data
        bool hasFloat;          // flag to return int or double
    };

}

#endif