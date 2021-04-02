// Specification file for Evaluator class
//
// This class provides methods for converting an expression from infix to 
// postfix and evaluating it.

#ifndef EVALUATOR_H
#define EVALUATOR_H

#include "Hashtable.h"
#include "Parser.h"
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
        void showSymTable();
    private:
        // Helper functions
        bool isVar(string tk);    // SymbolTable lookup
        // Member variables
        Parser tknr;         // used to parse out tokens in evaluate
        SymbolTable vars;    // stores variables and data
    };

}

#endif