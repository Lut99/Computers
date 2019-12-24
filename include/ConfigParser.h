/* CONFIG_PARSER.h
*    by tHE iNCREDIBLE mACHINE
*
*  Header file for ConfigParser.cpp.
**/

#ifndef CONFIGPARSER_H
#define CONFIGPARSER_H

#include <map>
#include <fstream>
#include <string>

namespace Parser {
    class ConfigParser {
        private:
            std::ifstream file;
            bool handle_open;
            std::map<std::string, std::string> config;

            bool is_multiline_comment;

        public:
            const int err_int;
            const float err_float;

            /* This class parses a config. In this config, options are listed in the shape of "key"="value". Once called, creates a handle that is kept open until either close() is called or until the class is destroyed. Access the inner elements with get<T>(). */
            ConfigParser(std::string path);
            ~ConfigParser();

            /* Parses the entire file and puts the result in the inner config. Use this for small files. For dynamic parsing, see parse_next(). */
            void parse_all();
            /* Parses a single option. The option name is returned, and the value is stored in the inner config. Use this if the file is too large to put into memory at once. */
            std::string parse_next();

            /* Checks if the config parsed so far contains a given key */
            bool contains(std::string key);
            /* Returns a single value, and tries to parse to given type. Note that only string, int and float are supported as of now, and string is returned by default. */
            template <typename T = std::string> T get(std::string key);

            /* Closes the internal handle. Note that this is automatically called upon deconstructing the class. */
            void close();

            /* Returns the inner map in string representation */
            std::string to_string();
    };
}

#endif