// Specification file for ParseErr class
//
// This class provides a ParseErr object to be thrown in the parse class
// for invalid expressions.

#ifndef PARSEERR_H
#define PARSEERR_H

#include <string>       // for error message
#include <exception>    // for throwing parse error
namespace lomboy_a2 {

    class ParseErr : public std::exception {
    public:
        ParseErr() : error_msg("invalid expression") { }
        ParseErr(std::string msg) : error_msg(msg) { }
        const char* what() const throw() { return error_msg.c_str(); }
    private:
        std::string error_msg;
    };

}

#endif