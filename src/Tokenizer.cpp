// Implementation file for Tokenizer class
// File name: Tokenizer.cpp

#include "Tokenizer.h"
#include <iostream>     // for cout
#include <cassert>
using namespace std;
namespace lomboy_a2 {

    // Default constructor sets values to defaults
    Tokenizer::Tokenizer() : str(""), delimiters(" "), index(0), retDelim(true) { }

    // Parametrized constructor sets member variables to arguments and index to 0
    Tokenizer::Tokenizer(string str, string delims)
        : str(str), delimiters(delims), index(0), retDelim(true) { }

    // Copy constructor copies member variables
    Tokenizer::Tokenizer(const Tokenizer& tkn) {
        str = tkn.str;
        delimiters = tkn.delimiters;
        index = tkn.index;
        retDelim = tkn.retDelim;
    }

    // Sets str member to be tokenized
    void Tokenizer::setStr(string str) {
        this->str = str;
    }

    // Sets delimiters for parsing
    void Tokenizer::setDelims(string delims) {
        delimiters = delims;
    }

    // Sets retDelim to true or false
    // If true, getNextToken() method will return delimiters as tokens if found in str.
    void Tokenizer::returnDelim(bool tf) {
        retDelim = tf;
    }            

    // Returns following token in str and moves index to next position for future use
    // If retDelim is true, will also return delimiters as tokens if found
    // If char is part of ignores, it will skip them
    string Tokenizer::getNextToken() {
        string token = "";                   // to return processed token
        bool foundDelim = false;             // flag

        // if index already at end of str, reset
        if (!hasNext()) {
            cout << "End of string reached. Resetting index to start...\n";
            index = 0;
        }

        // check that there are still tokens to read and delimiter not found
        while (hasNext() && !foundDelim) {

            // if delimiter, add to token, increment count and set flag
            if (isDelim(str[index])) {
                token += str[index++];
                foundDelim = true;
            }
            // if number, add to token then check if float
            else if (isdigit(str[index])) {
                token += str[index++];

                // if float, add decimal point and digits to token (and increment index)
                if (str[index] == '.') {
                    while (isdigit(str[index]) && hasNext()) token += str[index++];
                }

                foundDelim = (isDelim(str[index]) ? true : false);
            }
            // else, is identifier (potential to check for invalid chars later...)
            else {
                // loop until delimiter found or end reached
                while (!isDelim(str[index]) && hasNext()) token += str[index++];

                foundDelim = true;
            }
        }

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