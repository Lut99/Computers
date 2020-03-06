/* SCANNER.hpp
 *   by Lut99
 *
 * Created:
 *   3/6/2020, 3:10:09 PM
 * Last edited:
 *   3/6/2020, 4:30:39 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   Scanner.cpp defines the custom scanner used in the GreeC parsing
 *   language. Additional to representing regex expressions, this parser
 *   uses advanced error handling (C++-style, see ScannerErrors.hpp) and
 *   can skip over comments like it is nothing. This is the header file.
**/

#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <istream>

namespace GreeC {
    enum Tokens {
        
    };

    class Scanner {
        private:
            std::istream& in;
        public:
            /* The Scanner class can scan one file and returns the tokens one-by-one. */
            Scanner(std::istream& input);
            ~Scanner();

            /* Retrieves the next token in the input stream. */
             next_token();
    };
}

#endif