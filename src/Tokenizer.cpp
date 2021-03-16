// Implementation file for Tokenizer class
// File name: Tokenizer.cpp

#include "Tokenizer.h"
#include <cassert>
using namespace std;
namespace lomboy_a2 {

    // Default constructor sets values to defaults
    Tokenizer::Tokenizer() : str(""), delimiters("\0"), index(0) { }

    // Parametrized constructor sets member variables to arguments and index to 0
    Tokenizer::Tokenizer(string str, string delims)
        : str(str), delimiters('\0' + delims), index(0) { }

    // Copy constructor copies member variables
    Tokenizer::Tokenizer(const Tokenizer& tkn) {
        str = tkn.str;
        delimiters = tkn.delimiters;
        index = tkn.index;
    }

    // Returns following token in str and moves index to next position for future use
    // Uses str as default if no input provided
    // Does NOT check if at end - yet!
    string Tokenizer::getNextToken() {
        string token;                   // to return processed token
        size_t endOfToken;              // either delimiter or npos
        endOfToken = str.find(delimiters);

        // check that there are still tokens to read
        assert(hasNext());

        // parse out string to get next token, then reposition index
        token = str.substr(index, endOfToken);
        index = endOfToken;

        return token;
    }

    // Returns true if there are more characters in string from index position
    bool Tokenizer::hasNext() {
        return index < str.length(); 
    }

    // Checks if a character is a delimter, returns true if so
    bool Tokenizer::isDelim(char c) {
        bool isDelim = false;
        size_t i = 0;

        // loop over all delimiters until match found or end reached
        while (i < delimiters.length() && !isDelim) {
            if (c == delimiters[i]) isDelim = true;
            i++;
        }

        return isDelim;
    }

    // void Tokenizer::reset()

}