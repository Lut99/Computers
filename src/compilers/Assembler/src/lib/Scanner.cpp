/* SCANNER.cpp
 *   by Lut99
 *
 * Created:
 *   3/23/2020, 12:29:29 PM
 * Last edited:
 *   3/26/2020, 5:22:15 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   The Scanner baseclass is a custom scanner for the Chaos Assembly
 *   Compiler. Each compiler language can derive from this class to scan
 *   for custom tokens, or leave the standard tokenization in place which
 *   should be good enough for most assembly languages.
**/

#include <iostream>
#include <cstring>
#include <cerrno>

#include "ScannerExceptions.hpp"
#include "Scanner.hpp"

using namespace std;
using namespace Assembler;

/* Returns if given char is a whitespace char. */
inline bool is_whitespace(char c) {
    return c == ' ' || c == '\t' || c == '\n';
}



/* The scanner class scans tokens from a given stream and returns each of those. Upon failure, the appropriate error is thrown. */
Scanner::Scanner(istream& file)
    : in(file),
    line(1),
    col(0),
    eof(false)
{}



/* Returns a new character token from the istream. Throws an error if it couldn't. */
char Scanner::get_token() {
    char c;
    this->in.get(c);
    if (this->in.eof()) {
        // Set the flag, return the c nonetheless
        this->eof = true;
        return c;
    } else if (this->in.fail()) {
        // Throw the error
        throw FileReadException(this->line, this->col, errno);
    }

    // Keep track of the string
    this->scan_buffer << c;

    // Increment line counters
    this->col++;
    if (c == '\n') {
        this->line++;
        this->col = 0;
    }

    return c;
}



/* Returns a token scanned from the istream. Note that it returns int, which can then be compared to the default set of tokens or a custom set of tokens. Returns -1 if no more tokens are available. */
int Scanner::getToken(unsigned long& value) {
    // If there is a token on the stack, return that instead
    if (this->stack.size() > 0) {
        int token = this->stack.at(this->stack.size() - 1);
        this->stack.pop_back();
        return token;
    }

    // Uses a hard-coded, final-state automaton to parse and find the _longest_ token in the stream.
    char c;
    int to_return;
    unsigned long count;
    value = 0;

start:
    this->scan_buffer.str("");
    this->scan_buffer.clear();
    to_return = -1;

    c = this->get_token();
    if (this->eof) { return to_return; }
    switch(c) {
        case '/': goto slash;
        case 's': goto s;
        case '$': goto reg_number;
        case '0': goto zero;
        case ' ': goto start;
        case '\n': goto start;
        default:
            if (c >= '1' && c <= '9') {
                this->in.putback(c);
                goto dec_number;
            }
            throw SyntaxError(this->line, this->col, this->scan_buffer.str());
    }

s:
    c = this->get_token();
    if (this->eof) { return to_return; }
    switch(c) {
        case 'e': goto se;
        default:
            throw SyntaxError(this->line, this->col, this->scan_buffer.str());
    }

se:
    c = this->get_token();
    if (this->eof) { return to_return; }
    switch(c) {
        case 't':
            // Final state; store this as a possible return value
            to_return = (int) set;
            // Nothing to go anymore, so return it
            return to_return;
        default:
            throw SyntaxError(this->line, this->col, this->scan_buffer.str());
    }

slash:
    c = this->get_token();
    if (this->eof) { return to_return; }
    switch(c) {
        case '/': goto line_comment;
        default:
            throw SyntaxError(this->line, this->col, this->scan_buffer.str());
    }

line_comment:
    c = this->get_token();
    if (this->eof) { return to_return; }
    switch(c) {
        case '\n': goto start;
        default: goto line_comment;
    }

zero:
    c = this->get_token();
    if (this->eof) { return to_return; }
    if (c == 'x') {
        count = 0;
        goto hex_number;
    } else if (c >= '0' && c <= '9') {
        this->in.putback(c);
        goto dec_number;
    } else {
        throw SyntaxError(this->line, this->col, this->scan_buffer.str());
    }

dec_number:
    count = value;
    c = this->get_token();
    if (this->eof) { return to_return; }
    if (c >= '0' && c <= '9') {
        value *= 10;
        value += (int) (c - '0');
        if (value < count) { throw DecOverflowError(this->line, this->col, this->scan_buffer.str()); }
        goto dec_number;
    } else if (is_whitespace(c)) {
        // Done
        return dec_const;
    } else {
        throw SyntaxError(this->line, this->col, this->scan_buffer.str());
    }

hex_number:
    c = this->get_token();
    if (this->eof) { return to_return; }
    if (c >= '0' && c <= '9') {
        if (count >= 16) { throw HexOverflowError(this->line, this->col, this->scan_buffer.str()); }
        value *= 16;
        value += (c - '0');
        count++;
        goto hex_number;
    } else if (c >= 'A' && c <= 'F') {
        if (count >= 16) { throw HexOverflowError(this->line, this->col, this->scan_buffer.str()); }
        value *= 16;
        value += ((int) (c - 'A')) + 10;
        count++;
        goto hex_number;
    } else if (is_whitespace(c)) {
        // Done
        return hex_const;
    } else {
        throw SyntaxError(this->line, this->col, this->scan_buffer.str());
    }

reg_number:
    c = this->get_token();
    if (this->eof) { return to_return; }
    if (c >= '0' && c <= '9') {
        value *= 10;
        value += (int) (c - '0');
        if (value >= 16) { throw RegOverflowError(this->line, this->col, this->scan_buffer.str()); }
        goto reg_number;
    } else if (is_whitespace(c)) {
        // Done
        return reg_const;
    } else {
        throw SyntaxError(this->line, this->col, this->scan_buffer.str());
    }
}

/* Puts given token back on the stream so that it may be parsed again. Note that, for simplicity, it is put back on a temporary stack, which means this can only be done a fixed number of times. */
void Scanner::putToken(int token) {
    this->stack.push_back(token);
}
