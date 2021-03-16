// Implementation file for Tokenizer class
// File name: Tokenizer.cpp

#include "Tokenizer.h"
#include <iostream>     // for cout
#include <cassert>
using namespace std;
namespace lomboy_a2 {

    // Default constructor sets values to defaults
    Tokenizer::Tokenizer() : str(""), delimiters(" "), ignores(" "), index(0), retDelims(true) { }

    // Parametrized constructor sets member variables to arguments and index to 0
    Tokenizer::Tokenizer(string str, string delims)
        : str(str), delimiters(delims), ignores(" "), index(0), retDelims(true) { }

    // Copy constructor copies member variables
    Tokenizer::Tokenizer(const Tokenizer& tkn) {
        str = tkn.str;
        delimiters = tkn.delimiters;
        ignores = tkn.ignores;
        index = tkn.index;
        retDelims = tkn.retDelims;
    }

    // Sets str member to be tokenized
    void Tokenizer::setStr(string str) {
        this->str = str;
    }

    // Sets delimiters for parsing
    void Tokenizer::setDelims(string delims) {
        delimiters = delims;
    }

    // Sets retDelims to true or false
    // If true, getNextToken() method will return delimiters as tokens if found in str.
    void Tokenizer::returnDelims(bool tf) {
        retDelims = tf;
    }            

    // Returns following token in str and moves index to next position for future use
    // If retDelims is true, will also return delimiters as tokens if found
    // If char is part of ignores, it will skip them
    string Tokenizer::getNextToken() {
        string token = "";                   // to return processed token
        bool endToken = false;             // flag

        // if index already at end of str, reset
        if (!hasNext()) {
            cout << "End of string reached. Resetting index to start...\n";
            index = 0;
        }

        // check that there are still tokens to read and delimiter not found
        while (hasNext() && !endToken) {

            // if delimiter and set to be tokenized, add to token, increment count and set flag
            // else if not returnDelim, skip (by not ending token)
            if (isDelim(str[index])) {
                if(retDelims && !isIgnored(str[index])) {
                    token += str[index];
                    endToken = true;
                }

                index++;
            }
            // if number, add to token then check if float
            else if (isdigit(str[index])) {
                token += str[index++];

                // if float, add decimal point and digits to token (and increment index)
                if (str[index] == '.') {
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

    // Returns true if there are more characters in string from index position
    bool Tokenizer::hasNext() {
        return index < str.length(); 
    }

    // Checks if a character is a delimter, returns true if so
    bool Tokenizer::isDelim(char c) {
        return isFound(c, delimiters);
    }

    // Checks if a character is part of ignores, returns true if so
    bool Tokenizer::isIgnored(char c) {
        return isFound(c, ignores);
    }


    // Checks if a character is part of a string, returns true if so
    // To be used with isDelim and isIgnored
    bool Tokenizer::isFound(char c, string chars) {
        bool isFound = false;
        size_t i = 0;

        // loop over all chars until match found or end reached
        while (i < chars.length() && !isFound) {
            if (c == chars[i]) isFound = true;
            i++;
        }

        return isFound;
    }

}