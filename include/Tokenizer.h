// Specification file for Tokenizer class
//
// This class takes a string and provides methods for tokenizing it.

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
namespace lomboy_a2 {

    class Tokenizer {
    public:
        // Constructors
        Tokenizer();
        Tokenizer(std::string str, std::string delims);
        Tokenizer(const Tokenizer& tkn);
        // Modification methods
        void setStr(std::string str);
        void setDelims(std::string delims);
        std::string getNextToken();
        void reset();
        // Constant methods
        std::string getStr() { return str; }
        std::string getDelims() { return delimiters; }
        size_t getIndex() { return index; }
        bool isDelim(char c);
    private:
        // Helper functions
        bool hasNext();
        // Member variables
        std::string str;
        std::string delimiters;
        size_t index;       // keeps track of current string position
    };

}

#endif