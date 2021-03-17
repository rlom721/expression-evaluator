// Specification file for Tokenizer class
//
// This class takes a string and provides methods for tokenizing it.

#ifndef TOKENIZER_H
#define TOKENIZER_H

#include <string>
// #include <vector>
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
        void setIgnores(std::string ignores);
        void returnDelims(bool tf);             // sets retDelim
        std::string getNextToken();
        void reset();
        // Constant methods
        bool hasNext();
        std::string getStr() { return str; }
        std::string getDelims() { return delimiters; }
        std::string getIgnores() { return ignores; }
        // size_t getIndex() { return index; }
    private:
        // Helper functions
        bool isDelim(char c); 
        bool isIgnored(char c); 
        bool isFound(char c, std::string chars); 
        // Member variables
        std::string str;
        std::string delimiters;
        std::string ignores;
        // std::vector<std::string> tokens;
        // vector<std::string> keyWords; // parse key words...
        size_t index;         // keeps track of current string position
        bool retDelims;        // getNextToken will return delimiters
    };

}

#endif