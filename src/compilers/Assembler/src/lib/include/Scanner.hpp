/* SCANNER.hpp
 *   by Lut99
 *
 * Created:
 *   3/23/2020, 12:30:22 PM
 * Last edited:
 *   3/23/2020, 1:23:40 PM
 * Auto updated?
 *   Yes
 *
 * Description:
 *   The Scanner baseclass is a custom scanner for the Chaos Assembly
 *   Compiler. Each compiler language can derive from this class to scan  *
 *   for custom tokens, or leave the standard tokenization in place which
 *   should be good enough for most assembly languages.
**/

#ifndef SCANNER_HPP
#define SCANNER_HPP

#include <fstream>
#include <sstream>
#include <string>
#include <vector>

namespace Assembler {
    class Scanner {
        protected:
            /* Ifstream object referring to file given to us. */
            std::istream& in;
            /* Temporary stack to put tokens on that are put back there. */
            std::vector<int> stack;
            /* Keeps track of scanned text for the current token. */
            std::stringstream scan_buffer;
            /* Keeps track of the line number the scanner is currently in. */
            unsigned long line;
            /* Keeps track of the column number the scanner is currently in. */
            unsigned long col;

            /* Returns a new character token from the istream. Throws an error if it couldn't. */
            char get_token();
        public:
            /* Defines a list of tokens that are returned by the Scanner. Child classes can of course declare their own. */
            enum tokens {
                set
            };

            /* Notifies if the eof has been reached. */
            bool eof;

            /* The scanner class scans tokens from a given stream and returns each of those. Upon failure, the appropriate error is thrown. */
            Scanner(std::istream& file);

            /* Returns a token scanned from the istream. Note that it returns int, which can then be compared to the default set of tokens or a custom set of tokens. Returns -1 if no more tokens are available. */
            virtual int getToken();
            /* Puts given token back on the stream so that it may be parsed again. Note that, for simplicity, it is put back on a temporary stack, which means this can only be done a fixed number of times. */
            virtual void putToken(int token);
    };
}

#endif