// Specification file for Evaluator class
//
// This class provides methods for converting an expression from infix to 
// postfix and evaluating it.

#ifndef EVALUATOR_H
#define EVALUATOR_H

// #include "SymbolTable.h"
#include "Tokenizer.h"
#include <string>
namespace lomboy_a2 {

    // return MOST PRECISE... so int or float? how tho...

    class Evaluator {
    public:
        // Constructors
        Evaluator();
        Evaluator(std::string str, std::string delims);
        Evaluator(const Evaluator& tkn);    // copy
        // Modification methods
        // Constant methods
        std::string infixToPostfix(std::string expression);
        double evaluate(std::string expression);  // hmm can be int tho...
    private:
        // Helper functions
        bool isOperand();
        bool isIdentifier();    // SymbolTable lookup
        // Member variables
        Tokenizer tknr;
        // SymbolTable identifiers;    // stores variables and data
        bool hasFloat;          // flag to return int or double
        // std::string expression // ?
    };

}

#endif